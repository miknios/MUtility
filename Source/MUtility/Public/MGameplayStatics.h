// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class MUTILITY_API UMGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static AActor* StaticSpawnActorFromClass(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FTransform Transform);
};
