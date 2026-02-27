// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MClass.generated.h"

namespace M::Class
{
	FString GetClassDisplayName(const UClass& Class);
}

UCLASS()
class UMClassLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "M|Class")
	static FString GetClassDisplayName(const UClass* Class);
};
