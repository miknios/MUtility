// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MUtilityTypes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMDynamicMulticastDelegateSignature);

UENUM(BlueprintType)
enum class ELeftRightSide : uint8
{
	Left,
	Right
};

UENUM(BlueprintType)
enum class EMCollisionShape : uint8
{
	Box,
	Sphere,
	Capsule,
	Line UMETA(DisplayName = "Line (can't be used for overlap)")
};
