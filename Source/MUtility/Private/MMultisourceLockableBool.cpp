// Copyright (c) Miknios. All rights reserved.


#include "MMultisourceLockableBool.h"

bool UMMultisourceLockableBool::IsActive() const
{
	return BlockSources.IsEmpty();
}

void UMMultisourceLockableBool::AddBlockSource(const UObject* BlockSource)
{
	const bool bActiveOld = IsActive();
	
	BlockSources.Emplace(BlockSource);
	const bool bActiveNew = IsActive();

	if (bActiveOld != bActiveNew)
	{
		OnValueChangedDelegate.Broadcast(bActiveNew);
	}
}

void UMMultisourceLockableBool::RemoveBlockSource(const UObject* BlockSource)
{
	const bool bActiveOld = IsActive();
	
	BlockSources.Remove(BlockSource);
	const bool bActiveNew = IsActive();

	if (bActiveOld != bActiveNew)
	{
		OnValueChangedDelegate.Broadcast(bActiveNew);
	}
}
