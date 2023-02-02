// Copyright 2022 Mickael Daniel. All Rights Reserved.

#pragma once

#include "ModelView/HeartGraphSchema.h"
#include "HeartProxy_ComboGraphSchema.generated.h"

/**
 *
 */
UCLASS()
class COMBOGRAPHHEARTPROXY_API UHeartProxy_ComboGraphSchema : public UHeartGraphSchema
{
	GENERATED_BODY()

	virtual UClass* GetConnectionVisualizerClass_Implementation() const override;
};
