#pragma once

#include "Model/HeartGraph.h"
#include "HeartProxy_ComboGraph.generated.h"

class UComboGraph;
class UComboGraphNodeBase;
class UHeartAction_ComboGraphProxify;

/**
 *
 */
UCLASS()
class COMBOGRAPHHEARTPROXY_API UHeartProxy_ComboGraph : public UHeartGraph
{
	GENERATED_BODY()

	friend class UHeartAction_ComboGraphProxify;

public:
	UHeartProxy_ComboGraph();

#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual TSubclassOf<UHeartGraphSchema> GetSchemaClass_Implementation() const override;

	void RunProxyAction();

protected:
	UPROPERTY(EditInstanceOnly)
	TObjectPtr<UComboGraph> ComboGraphAsset;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UHeartAction_ComboGraphProxify> ProxificationAction;
};

UCLASS()
class UComboGraphAsHeartProxyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UHeartGraph* CreateHeartProxy(UComboGraph* ComboGraph, TSubclassOf<UHeartAction_ComboGraphProxify> ProxificationSettings);
};
