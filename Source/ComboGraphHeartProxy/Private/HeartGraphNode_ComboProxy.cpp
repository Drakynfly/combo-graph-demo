#include "HeartGraphNode_ComboProxy.h"

#include "ComboNodeProxy.h"

UHeartGraphNode_ComboProxy::UHeartGraphNode_ComboProxy()
{
	auto&& SparseClassStruct = GetHeartGraphNodeSparseClassData();
	SparseClassStruct->DefaultInputs.Add("Inputs", FHeartGraphPinType());
	SparseClassStruct->DefaultOutputs.Add("Outputs", FHeartGraphPinType());
}

FText UHeartGraphNode_ComboProxy::GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const
{
	if (Context == EHeartNodeNameContext::NodeInstance)
	{
		if (auto&& ComboProxy = GetNodeObject<UComboNodeProxyBase>())
		{
			return ComboProxy->GetNodeTitle();
		}
	}

	return Super::GetNodeTitle_Implementation(Node, Context);
}

bool UHeartGraphNode_ComboProxy::CanCreate_Implementation() const
{
	return false;
}
