// Copyright (c) Miknios. All rights reserved.


#include "MAnimation.h"

UAnimMontage* MAnimation::GetOrCreateDynamicMontage(UAnimSequenceBase* AnimSequence, FName SlotNodeName,
                                                    float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount,
                                                    float BlendOutTriggerTime, float InTimeToStartMontageAt)
{
	if (AnimSequence == nullptr)
	{
		return nullptr;
	}

	if (UAnimMontage* Montage = Cast<UAnimMontage>(AnimSequence))
	{
		return Montage;
	}

	UAnimMontage* DynamicMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(
		AnimSequence, SlotNodeName, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
	return DynamicMontage;
}

float MAnimation::CalculateAnimPlayRateFromDuration(const float SourceDuration, const float TargetDuration)
{
	const float Result = SourceDuration / TargetDuration;
	return Result;
}
