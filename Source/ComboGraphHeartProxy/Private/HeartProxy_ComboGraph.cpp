#include "HeartProxy_ComboGraph.h"

#include "HeartAction_ComboGraphProxify.h"
#include "HeartProxy_ComboGraphSchema.h"
#include "ModelView/Actions/HeartGraphAction.h"

#include "Graph/ComboGraph.h"

#include "UObject/ObjectSaveContext.h"

UHeartProxy_ComboGraph::UHeartProxy_ComboGraph()
{
#if WITH_EDITOR
	GetHeartGraphSparseClassData()->CanCreateAssetFromFactory = true;
#endif
}

#if WITH_EDITOR

void UHeartProxy_ComboGraph::PreSave(FObjectPreSaveContext SaveContext)
{
	//RunProxyAction();
	Super::PreSave(SaveContext);
}

void UHeartProxy_ComboGraph::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UHeartProxy_ComboGraph, ComboGraphAsset) ||
		PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UHeartProxy_ComboGraph, ProxificationAction))
	{
		RunProxyAction();
	}
}

#endif

TSubclassOf<UHeartGraphSchema> UHeartProxy_ComboGraph::GetSchemaClass_Implementation() const
{
	return UHeartProxy_ComboGraphSchema::StaticClass();
}

void UHeartProxy_ComboGraph::RunProxyAction()
{
	if (IsValid(ProxificationAction) && IsValid(ComboGraphAsset))
	{
		UHeartAction_ComboGraphProxify* ProxyAction = NewObject<UHeartAction_ComboGraphProxify>(this, ProxificationAction);
		if (ProxyAction->Execute(this, FHeartInputActivation(), ComboGraphAsset.Get()))
		{
		}
	}
}

UHeartGraph* UComboGraphAsHeartProxyLibrary::CreateHeartProxy(UComboGraph* ComboGraph, TSubclassOf<UHeartAction_ComboGraphProxify> ProxificationSettings)
{
	if (IsValid(ProxificationSettings) && IsValid(ComboGraph))
	{
		UHeartProxy_ComboGraph* ProxyGraph = NewObject<UHeartProxy_ComboGraph>();

		UHeartAction_ComboGraphProxify* ProxyAction = NewObject<UHeartAction_ComboGraphProxify>(GetTransientPackage(), ProxificationSettings);
		if (ProxyAction->Execute(ProxyGraph, FHeartInputActivation(), ComboGraph))
		{
			return ProxyGraph;
		}
	}

	return nullptr;
}
