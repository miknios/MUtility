﻿// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"

#include "MTeamDefinition.generated.h"

USTRUCT(BlueprintType)
struct MUTILITY_API FMTeamAttitudeOverride
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetOptions = "MUtility.MTeamLibrary.GetTeamNames"))
	FName TeamA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetOptions = "MUtility.MTeamLibrary.GetTeamNames"))
	FName TeamB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETeamAttitude::Type> Attitude = ETeamAttitude::Neutral;
};

USTRUCT(BlueprintType)
struct MUTILITY_API FMTeamDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName TeamName;
};
