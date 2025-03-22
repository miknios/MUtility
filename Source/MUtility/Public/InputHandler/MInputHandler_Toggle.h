// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MInputHandler_Base.h"
#include "MInputHandler_Toggle.generated.h"

/**
 * 
 */
UCLASS()
class MUTILITY_API UMInputHandler_Toggle : public UMInputHandler_Base
{
	GENERATED_BODY()

public:
	virtual void SetInputHeld(const bool bInInputHeld, const bool bControlledStateCurrent) override;

protected:
	bool bInputHeld;
	bool bInputHeldOld;
};
