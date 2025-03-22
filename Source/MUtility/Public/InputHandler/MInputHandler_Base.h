// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MInputHandler_Base.generated.h"

UENUM(BlueprintType)
enum class EMInputHandlerType : uint8
{
	Hold,
	Toggle,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMOnInputHandlerUpdateSignature, bool, bControlledStateNew);

/**
 * 
 */
UCLASS()
class MUTILITY_API UMInputHandler_Base : public UObject
{
	GENERATED_BODY()

public:
	virtual void SetInputHeld(const bool bInInputHeld, const bool bControlledStateCurrent);
	virtual void SetControlledStateChangedExternally(bool bStateNew);

	UPROPERTY(BlueprintAssignable)
	FMOnInputHandlerUpdateSignature OnInputHandlerUpdateDelegate; 
};
