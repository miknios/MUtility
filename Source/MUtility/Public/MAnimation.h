// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"

namespace MAnimation
{
	// Returns AnimSequence casted to AnimMontage or creates a new Dynamic Montage from it
	// Additional parameters are only used when creating new Dynamic Montage
	MUTILITY_API UAnimMontage* GetOrCreateDynamicMontage(UAnimSequenceBase* AnimSequence, FName SlotNodeName,
	                                                     float BlendInTime = 0.25f, float BlendOutTime = 0.25f, float InPlayRate = 1.f,
	                                                     int32 LoopCount = 1, float BlendOutTriggerTime = -1.f,
	                                                     float InTimeToStartMontageAt = 0.f);

	MUTILITY_API float CalculateAnimPlayRateFromDuration(float SourceDuration, float TargetDuration);
}
