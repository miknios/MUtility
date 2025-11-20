// Copyright (c) Miknios. All rights reserved.


#include "Condition/MGameplayCondition_Compositor.h"

bool UMGameplayCondition_Compositor::Evaluate_Impl_Implementation(UWorld* World)
{
	bool bOrResult = false;
	for (UMGameplayCondition_Base* Condition : Conditions)
	{
		if (Condition == nullptr)
		{
			continue;
		}

		const bool bEvaluationResult = Condition->Evaluate(World);
		bOrResult |= bEvaluationResult;

		if (CompositionType == EMConditionCompositionType::AND && !bEvaluationResult)
		{
			return false;
		}
	}

	const bool bResult = CompositionType == EMConditionCompositionType::AND
		                     ? true
		                     : bOrResult;
	return bResult;
}

void UMGameplayCondition_Compositor::ListenForChanges_Implementation(UWorld* World)
{
	for (UMGameplayCondition_Base* Condition : Conditions)
	{
		if (Condition == nullptr)
		{
			continue;
		}

		Condition->OnConditionSourceChangedDelegate.AddDynamic(this, &UMGameplayCondition_Compositor::OnInternalConditionChanged);
		Condition->ListenForChanges(World);
	}
}

void UMGameplayCondition_Compositor::StopListeningForChanges_Implementation(UWorld* World)
{
	for (UMGameplayCondition_Base* Condition : Conditions)
	{
		if (Condition == nullptr)
		{
			continue;
		}

		Condition->OnConditionSourceChangedDelegate.RemoveDynamic(this, &UMGameplayCondition_Compositor::OnInternalConditionChanged);
		Condition->StopListeningForChanges(World);
	}
}

// TODO: implement this - append all conditions and composition type to string
FString UMGameplayCondition_Compositor::GetConditionDescriptionString_Implementation() const
{
	return TEXT("");
}

void UMGameplayCondition_Compositor::OnInternalConditionChanged()
{
	OnConditionSourceChangedDelegate.Broadcast();
}
