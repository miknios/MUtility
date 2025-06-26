// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MMeshStatics.generated.h"

UCLASS()
class MUTILITY_API UMMeshStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void AttachComponentsSocketAligned(USceneComponent* ChildComponent, FName ChildSocket,
	                                          USceneComponent* ParentComponent, FName ParentSocket);
};
