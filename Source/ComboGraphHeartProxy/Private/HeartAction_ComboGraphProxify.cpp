#include "HeartAction_ComboGraphProxify.h"
#include "HeartGraphNode_ComboProxy.h"
#include "ComboNodeProxy.h"
#include "HeartProxy_ComboGraph.h"

#include "Model/HeartGraph.h"

#include "Graph/ComboGraph.h"
#include "Graph/ComboGraphEdge.h"
#include "Graph/ComboGraphNodeBase.h"
#include "Model/HeartGraphNode.h"

void UHeartAction_ComboGraphProxify::ExecuteOnGraph(UHeartGraph* Graph, const FHeartInputActivation& Activation, UObject* ContextObject)
{
	Super::ExecuteOnGraph(Graph, Activation, ContextObject);

	auto&& ProxyGraph = Cast<UHeartProxy_ComboGraph>(Graph);
	auto&& ComboGraph = Cast<UComboGraph>(ContextObject);

	if (!IsValid(ComboGraph))
	{
		return;
	}


	/// STEP 0: Reset Proxy Graph

	TArray<UHeartGraphNode*> Nodes;
	ProxyGraph->GetNodeArray(Nodes);
	for (auto&& Node : Nodes)
	{
		ProxyGraph->RemoveNode(Node->GetGuid());
	}

	TMap<TObjectPtr<UComboGraphNodeBase>, FHeartNodeGuid> Proxies;

	/// STEP 1: Recreate Combo Graph nodes

	TSet<TObjectPtr<UComboGraphEdge>> UniqueEdges;

	// @todo doesnt seem to be an easy way to extract the edgraph node location, so we might have to recreate the node
	// layout ourselves. fake it for now
	FVector2D Location = FVector2D::ZeroVector;

	for (auto&& ComboNode : ComboGraph->AllNodes)
	{
		UClass* ComboNodeClass = ComboNode->GetClass();

		if (auto&& ProxyClass = ProxyNodeClasses.Find(ComboNodeClass))
		{
			if (auto&& ProxyNode = ProxyGraph->CreateNodeFromClass<UHeartGraphNode_ComboProxy>(*ProxyClass, Location))
			{
				ProxyNode->GetNodeObject<UComboNodeProxyBase>()->ComboNode = ComboNode;
				ProxyGraph->AddNode(ProxyNode);

				Proxies.Add(ComboNode, ProxyNode->GetGuid());

				Location.X += 300;
			}
		}

		TArray<TObjectPtr<UComboGraphEdge>> Edges;
		ComboNode->Edges.GenerateValueArray(Edges);
		UniqueEdges.Append(Edges);
	}


	/// STEP 2: Recreate Combo Graph connections

	for (auto&& Edge : UniqueEdges)
	{
		auto&& StartProxy = Proxies.Find(Edge->StartNode);
		auto&& EndProxy = Proxies.Find(Edge->EndNode);

		if (!StartProxy || !EndProxy)
		{
			continue;
		}

		auto&& StartPin = ProxyGraph->GetNode(*StartProxy)->GetPinByName("Outputs");
		auto&& EndPin = ProxyGraph->GetNode(*EndProxy)->GetPinByName("Inputs");

		if (StartPin && EndPin)
		{
			StartPin->ConnectTo(EndPin);
		}
	}
}
