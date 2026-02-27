// Copyright (c) Miknios. All rights reserved.


#include "Condition/MGameplayCondition_Base.h"

bool UMGameplayCondition_Base::Evaluate_Impl_Implementation(const UObject* ContextObject)
{
	return false;
}

void UMGameplayCondition_Base::ListenForChanges_Impl_Implementation(const UObject* ContextObject)
{
}

void UMGameplayCondition_Base::StopListeningForChanges_Impl_Implementation(const UObject* ContextObject)
{
}

FString UMGameplayCondition_Base::GetConditionDescriptionString_Implementation() const
{
	return TEXT("");
}

bool UMGameplayCondition_Base::Evaluate(const UObject* ContextObjectOverride)
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	bool bResult = Evaluate_Impl(ContextObject);
	if (bInvertCondition)
	{
		bResult = !bResult;
	}
	
	return bResult;
}

void UMGameplayCondition_Base::ListenForChanges(const UObject* ContextObjectOverride)
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	ListenForChanges_Impl(ContextObject);
}

void UMGameplayCondition_Base::StopListeningForChanges(const UObject* ContextObjectOverride)
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	StopListeningForChanges_Impl(ContextObject);
}

void UMGameplayCondition_Base::BroadcastOnConditionSourceChanged()
{
	OnConditionSourceChangedDelegate.Broadcast();
}

const UObject* UMGameplayCondition_Base::GetDefaultContextObject() const
{
	const AActor* ActorContext = GetTypedOuter<AActor>();
	if (ActorContext != nullptr)
	{
		return ActorContext;
	}

	const AController* ControllerContext = GetTypedOuter<AController>();
	if (ControllerContext != nullptr)
	{
		return ControllerContext;
	}

	const UWorld* WorldContext = GetWorld();
	return WorldContext;
}

const UObject* UMGameplayCondition_Base::GetDefaultContextOrOverride(const UObject* ContextObjectOverride) const
{
	if (ContextObjectOverride != nullptr)
	{
		return ContextObjectOverride;
	}
	
	return GetDefaultContextObject();
}
