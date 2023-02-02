// Copyright 2022 Mickael Daniel. All Rights Reserved.

#include "HeartProxy_ComboGraphSchema.h"
#include "HeartCanvasConnectionVisualizer.h"

UClass* UHeartProxy_ComboGraphSchema::GetConnectionVisualizerClass_Implementation() const
{
	return UHeartCanvasConnectionVisualizer::StaticClass();
}
