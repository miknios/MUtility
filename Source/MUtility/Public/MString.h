// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MString.generated.h"

UCLASS()
class MUTILITY_API UMString : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString ToString(const bool Value);

	template <typename EnumType>
	FORCEINLINE static FString EnumToString(const EnumType EnumeratorValue)
	{
		return UEnum::GetDisplayValueAsText(EnumeratorValue).ToString();
	}
};
