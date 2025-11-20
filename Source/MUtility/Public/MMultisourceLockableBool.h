// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MMultisourceLockableBool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMOnMultisourceLockableBoolValueChangedSignature, bool, IsActiveNew);

/**
 * Allows multiple sources to lock a bool value
 * IsActive returns true if no block sources are added
 */
UCLASS()
class MUTILITY_API UMMultisourceLockableBool : public UObject
{
	GENERATED_BODY()

public:
	// Returns true if no block sources are added
	UFUNCTION(BlueprintCallable)
	bool IsActive() const;

	UFUNCTION(BlueprintCallable)
	void AddBlockSource(const UObject* BlockSource);

	UFUNCTION(BlueprintCallable)
	void RemoveBlockSource(const UObject* BlockSource);

public:
	UPROPERTY(BlueprintAssignable)
	FMOnMultisourceLockableBoolValueChangedSignature OnValueChangedDelegate;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Activation Bool|Debug")
	TSet<const UObject*> BlockSources;
};
