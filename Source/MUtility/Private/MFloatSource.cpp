// Copyright (c) Miknios. All rights reserved.


#include "MFloatSource.h"

void UMFloatSource_Base::ListenForChanges_Implementation()
{
}

void UMFloatSource_Base::StopListeningForChanges_Implementation()
{
}

float UMFloatSource_Base::GetFloatValue_Implementation(UObject* ContextObject) const
{
	return 0.0f;
}

void UMFloatSource_Base::BroadcastOnValueChanged()
{
	OnValueChangedDelegate.Broadcast();
}

float UMFloatSource_Static::GetFloatValue_Implementation(UObject* ContextObject) const
{
	return FloatValue;
}
