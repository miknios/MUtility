// Copyright (c) Miknios. All rights reserved.


#include "Condition/MGameplayCondition_Base.h"

bool UMGameplayCondition_Base::Evaluate_Impl_Implementation(const UWorld* World)
{
	return false;
}

void UMGameplayCondition_Base::ListenForChanges_Implementation(const UWorld* World)
{
}

void UMGameplayCondition_Base::StopListeningForChanges_Implementation(const UWorld* World)
{
}

FString UMGameplayCondition_Base::GetConditionDescriptionString_Implementation() const
{
	return TEXT("");
}

bool UMGameplayCondition_Base::Evaluate(const UWorld* World)
{
	bool bResult = Evaluate_Impl(World);
	if (bInvertCondition)
	{
		bResult = !bResult;
	}
	
	return bResult;
}

void UMGameplayCondition_Base::BroadcastOnConditionSourceChanged()
{
	OnConditionSourceChangedDelegate.Broadcast();
}
