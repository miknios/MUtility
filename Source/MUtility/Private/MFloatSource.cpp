// Copyright (c) Miknios. All rights reserved.


#include "MFloatSource.h"

void UMFloatSource_Base::ListenForChanges_Impl_Implementation(const UObject* ContextObject)
{
}

void UMFloatSource_Base::StopListeningForChanges_Impl_Implementation(const UObject* ContextObject)
{
}

float UMFloatSource_Base::GetFloatValue_Impl_Implementation(const UObject* ContextObject) const
{
	return 0.0f;
}

float UMFloatSource_Base::GetFloatValue(const UObject* ContextObjectOverride) const
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	return GetFloatValue_Impl(ContextObject);
}

void UMFloatSource_Base::ListenForChanges(const UObject* ContextObjectOverride)
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	ListenForChanges_Impl(ContextObject);
}

void UMFloatSource_Base::StopListeningForChanges(const UObject* ContextObjectOverride)
{
	const UObject* ContextObject = GetDefaultContextOrOverride(ContextObjectOverride);
	StopListeningForChanges_Impl(ContextObject);
}

void UMFloatSource_Base::BroadcastOnValueChanged()
{
	OnValueChangedDelegate.Broadcast();
}

const UObject* UMFloatSource_Base::GetDefaultContextObject() const
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

const UObject* UMFloatSource_Base::GetDefaultContextOrOverride(const UObject* ContextObjectOverride) const
{
	if (ContextObjectOverride != nullptr)
	{
		return ContextObjectOverride;
	}
	
	return GetDefaultContextObject();
}

float UMFloatSource_Static::GetFloatValue_Impl_Implementation(const UObject* ContextObject) const
{
	return FloatValue;
}
