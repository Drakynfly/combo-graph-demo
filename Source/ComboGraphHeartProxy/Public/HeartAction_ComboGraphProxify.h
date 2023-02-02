#pragma once

#include "ModelView/Actions/HeartGraphAction.h"
#include "HeartAction_ComboGraphProxify.generated.h"

class UComboGraphNodeBase;
class UComboNodeProxyBase;

/**
 *
 */
UCLASS(Blueprintable)
class COMBOGRAPHHEARTPROXY_API UHeartAction_ComboGraphProxify : public UHeartGraphAction
{
	GENERATED_BODY()

public:
	virtual void ExecuteOnGraph(UHeartGraph* Graph, const FHeartInputActivation& Activation, UObject* ContextObject) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UComboGraphNodeBase>, TSubclassOf<UComboNodeProxyBase>> ProxyNodeClasses;
};
