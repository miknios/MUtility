// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MResettable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class MUTILITY_API UMResettable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement for things that can be reset
 * Useful for things like components attached to actor that should reset when actor is reinitialized to checkpoint
 */
class MUTILITY_API IMResettable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @param bHardReset should we clear state of the object completely. Non-hard reset preserves some state of the object like resources.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reset(bool bHardReset);
};
