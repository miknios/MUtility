// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayStatics.h"

AActor* UMGameplayStatics::StaticSpawnActorFromClass(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	FActorSpawnParameters SpawnParameters;
	AActor* SpawnedActor = WorldContextObject->GetWorld()->SpawnActor(ActorClass, &Transform);

	return SpawnedActor;
}

UMaterialInstanceDynamic* UMGameplayStatics::GetDynamicOverlayMaterialEnsure(UMeshComponent* MeshComponent)
{
	if (MeshComponent == nullptr)
	{
		return nullptr;
	}
	
	UMaterialInterface* MaterialInterface = MeshComponent->GetOverlayMaterial();
	if (MaterialInterface == nullptr)
	{
		return nullptr;
	}

	UMaterialInstanceDynamic* MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(MaterialInterface);
	if (MaterialInstanceDynamic == nullptr)
	{
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInterface, MeshComponent);
		MeshComponent->SetOverlayMaterial(MaterialInstanceDynamic);
	}

	return MaterialInstanceDynamic;
}
