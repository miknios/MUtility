// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MInputHandler_Base.h"
#include "MInputHandler_Hold.generated.h"

/**
 * 
 */
UCLASS()
class MUTILITY_API UMInputHandler_Hold : public UMInputHandler_Base
{
	GENERATED_BODY()

public:
	virtual void SetInputHeld(const bool bInInputHeld, const bool bControlledStateCurrent) override;
	virtual void SetControlledStateChangedExternally(bool bStateNew) override;

protected:
	bool bInputHeld;
	bool bInputHeldOld;
	bool bAwaitsInputUp;
};
