// Copyright (c) Miknios. All rights reserved.


#include "MFloatSource.h"

float UMFloatSource_Base::GetFloatValue_Implementation() const
{
	return 0.f;
}

void UMFloatSource_Base::ListenForChanges_Implementation()
{
}

void UMFloatSource_Base::StopListeningForChanges_Implementation()
{
}

void UMFloatSource_Base::BroadcastOnValueChanged()
{
	OnValueChangedDelegate.Broadcast();
}

float UMFloatSource_Static::GetFloatValue_Implementation() const
{
	return FloatValue;
}
