// Copyright (c) Miknios. All rights reserved.


#include "GameplayAction/MGameplayCondition_Action_IsActionActive.h"

#include "GameplayAction/MGameplayActionComponent.h"

bool UMGameplayCondition_Action_IsActionActive::Evaluate_Impl_Implementation(UWorld* World)
{
	UMGameplayActionComponent* ActionComponent = GetActionComponent();
	if (ActionComponent == nullptr)
	{
		return false;
	}
	
	UMGameplayActionInstance* ActionInstance = ActionComponent->FindOrAddActionInstance(ActionAsset);
	if (ActionInstance == nullptr)
	{
		return false;
	}

	return ActionInstance->IsActionActive();
}

void UMGameplayCondition_Action_IsActionActive::ListenForChanges_Implementation(UWorld* World)
{
	UMGameplayActionComponent* ActionComponent = GetActionComponent();
	if (ActionComponent == nullptr)
	{
		return;
	}
	
	UMGameplayActionInstance* ActionInstance = ActionComponent->FindOrAddActionInstance(ActionAsset);
	if (ActionInstance == nullptr)
	{
		return;
	}

	ActionInstance->OnActionStartedDelegate.AddDynamic(this, &UMGameplayCondition_Action_IsActionActive::OnActionStarted);
	ActionInstance->OnActionFinishedDelegate.AddDynamic(this, &UMGameplayCondition_Action_IsActionActive::OnActionFinished);
}

void UMGameplayCondition_Action_IsActionActive::StopListeningForChanges_Implementation(UWorld* World)
{
	UMGameplayActionComponent* ActionComponent = GetActionComponent();
	if (ActionComponent == nullptr)
	{
		return;
	}
	
	UMGameplayActionInstance* ActionInstance = ActionComponent->FindOrAddActionInstance(ActionAsset);
	if (ActionInstance == nullptr)
	{
		return;
	}

	ActionInstance->OnActionTriggered.RemoveDynamic(this, &UMGameplayCondition_Action_IsActionActive::OnActionStarted);
	ActionInstance->OnActionFinishedDelegate.RemoveDynamic(this, &UMGameplayCondition_Action_IsActionActive::OnActionFinished);
}

FString UMGameplayCondition_Action_IsActionActive::GetConditionDescriptionString_Implementation() const
{
	return Super::GetConditionDescriptionString_Implementation();
}

void UMGameplayCondition_Action_IsActionActive::OnActionStarted()
{
	OnConditionSourceChangedDelegate.Broadcast();
}

void UMGameplayCondition_Action_IsActionActive::OnActionFinished()
{
	OnConditionSourceChangedDelegate.Broadcast();
}
