#pragma once

#include "UObject/Object.h"
#include "ComboNodeProxy.generated.h"

class UComboGraphNodeBase;

/**
 *
 */
UCLASS(Abstract)
class COMBOGRAPHHEARTPROXY_API UComboNodeProxyBase : public UObject
{
	GENERATED_BODY()

public:
	FText GetNodeTitle() const;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UComboGraphNodeBase> ComboNode;
};

UCLASS()
class UComboProxy_MontageNode : public UComboNodeProxyBase
{
	GENERATED_BODY()

public:

};

UCLASS()
class UComboProxy_SequenceNode : public UComboNodeProxyBase
{
	GENERATED_BODY()

public:

};