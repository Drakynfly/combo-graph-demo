#pragma once

#include "Model/HeartGraphNode.h"
#include "HeartGraphNode_ComboProxy.generated.h"

/**
 *
 */
UCLASS()
class COMBOGRAPHHEARTPROXY_API UHeartGraphNode_ComboProxy : public UHeartGraphNode
{
	GENERATED_BODY()

	UHeartGraphNode_ComboProxy();

public:
	virtual FText GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const override;
	virtual bool CanCreate_Implementation() const override;
};
