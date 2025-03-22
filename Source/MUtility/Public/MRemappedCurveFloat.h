// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MRemappedCurveFloat.generated.h"

/**
 * Used as designer property for setting up a normalized curve with values remapped to (From, To) range 
 */
USTRUCT(BlueprintType)
struct MUTILITY_API FMRemappedCurveFloat
{
	GENERATED_BODY()

	FMRemappedCurveFloat()
		: Curve(nullptr),
		  From(0),
		  To(1)
	{
	}

	FMRemappedCurveFloat(UCurveFloat* Curve, float From, float To)
		: Curve(Curve),
		  From(From),
		  To(To)
	{
	}

	UPROPERTY(EditAnywhere)
	UCurveFloat* Curve;

	UPROPERTY(EditAnywhere)
	float From;

	UPROPERTY(EditAnywhere)
	float To;

	float GetValue(const float ProgressNormalized) const
	{
		if (Curve)
			return FMath::Lerp(From, To, Curve->GetFloatValue(ProgressNormalized));

		UE_LOG(LogTemp, Error, TEXT("Trying to get value from RemappedCurveFloat, but Curve is not set. Returning 0"))
		return 0;
	}
};
