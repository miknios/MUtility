// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayStatics.h"

AActor* UMGameplayStatics::StaticSpawnActorFromClass(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	FActorSpawnParameters SpawnParameters;
	AActor* SpawnedActor = WorldContextObject->GetWorld()->SpawnActor(ActorClass, &Transform);

	return SpawnedActor;
}
