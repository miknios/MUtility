﻿// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/ActorComponent.h"
#include "MTeamComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUTILITY_API UMTeamComponent : public UActorComponent, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// ~ IGenericTeamAgentInterface
	
	UFUNCTION(BlueprintCallable, Category = "Team")
	FName GetAssignedTeam() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (GetOptions = "MUtility.MTeamLibrary.GetTeamNames"))
	FName AssignedTeamName;
};
