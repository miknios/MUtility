// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMath.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MMathBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "MMath"))
class MUTILITY_API UMMathBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector FromToVector(const FVector& From, const FVector& To)
	{
		return MMath::FromToVector(From, To);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector FromToVectorNormalized(const FVector& From, const FVector& To)
	{
		return MMath::FromToVectorNormalized(From, To);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float AngleBetweenSignedRad(const FVector2D& From, const FVector2D& To)
	{
		return MMath::AngleBetweenSignedRad(From, To);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float AngleBetweenSignedDeg(const FVector2D& From, const FVector2D& To)
	{
		return MMath::AngleBetweenSignedDeg(From, To);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float AngleBetweenVectorsRad(const FVector& Vec1, const FVector& Vec2)
	{
		return MMath::AngleBetweenVectorsRad(Vec1, Vec2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float AngleBetweenVectorsDeg(const FVector& Vec1, const FVector& Vec2)
	{
		return MMath::AngleBetweenVectorsDeg(Vec1, Vec2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float SignedAngleBetweenVectorsRad(const FVector& Vec1, const FVector& Vec2)
	{
		return MMath::SignedAngleBetweenVectorsRad(Vec1, Vec2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float SignedAngleBetweenVectorsDeg(const FVector& Vec1, const FVector& Vec2)
	{
		return MMath::SignedAngleBetweenVectorsDeg(Vec1, Vec2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector ToHorizontalDirection(const FVector& Vector)
	{
		return MMath::ToHorizontalDirection(Vector);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetDirectorAlongSurfaceForDirection(const FVector& SurfaceNormal, const FVector& Direction)
	{
		return MMath::GetDirectorAlongSurfaceForDirection(SurfaceNormal, Direction);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector RotateDirectionTowardsTargetDirectionByAngle(
		const FVector& Direction, const FVector& DirectionTarget, const float AngleDeg)
	{
		return MMath::RotateDirectionTowardsTargetDirectionByAngle(Direction, DirectionTarget, AngleDeg);
	}
};
