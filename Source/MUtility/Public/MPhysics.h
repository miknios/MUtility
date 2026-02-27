// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MUtilityTypes.h"

#include "MPhysics.generated.h"

USTRUCT(BlueprintType)
struct MUTILITY_API FMCollisionShapeRef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMCollisionShape ShapeType = EMCollisionShape::Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (EditCondition = "ShapeType == EMCollisionShape::Box", EditConditionHides))
	FVector BoxExtent = FVector(10, 10, 10);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (EditCondition = "ShapeType == EMCollisionShape::Sphere", EditConditionHides))
	float SphereRadius = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (EditCondition = "ShapeType == EMCollisionShape::Capsule", EditConditionHides))
	float CapsuleRadius = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (EditCondition = "ShapeType == EMCollisionShape::Capsule", EditConditionHides))
	float CapsuleHalfHeight = 10;
};

namespace M::Physics
{
	MUTILITY_API FCollisionShape MakeCollisionShapeFromShapeRef(const FMCollisionShapeRef& ShapeRef);
	MUTILITY_API FMCollisionShapeRef MakeCollisionShapeRefFromCollisionShape(const FCollisionShape& Shape);

	MUTILITY_API void DrawCollisionShape(const UWorld* World, const FCollisionShape& CollisionShape, const FTransform& Transform,
	                                     const FColor& Color, const bool bPersistentLines = false, const float LifeTime = -1,
	                                     const uint8 DepthPriority = 0, const float Thickness = 0);

	MUTILITY_API void DrawCollisionShape(const UWorld* World, const FMCollisionShapeRef& ShapeRef, const FTransform& Transform,
	                                     const FColor& Color, const bool bPersistentLines = false, const float LifeTime = -1,
	                                     const uint8 DepthPriority = 0, const float Thickness = 0);

	MUTILITY_API void DrawTraceHitResult(const UWorld* World, const FHitResult& HitResult, const FCollisionShape& CollisionShape,
	                                     const FQuat& CollisionShapeRotation, const FColor& Color, const bool bPersistentLines = false,
	                                     const float LifeTime = -1, const uint8 DepthPriority = 0, const float Thickness = 0);
	
	MUTILITY_API void DrawCollisionShapePDI(FPrimitiveDrawInterface* PDI, const FMCollisionShapeRef& CollisionShape,
												  const FTransform& Transform,
												  const FColor& Color, float Thickness = 0);
	
	MUTILITY_API void DrawCollisionShapePDI(FPrimitiveDrawInterface* PDI, const FCollisionShape& CollisionShape,
												  const FTransform& Transform,
												  const FColor& Color, float Thickness = 0);
	
	MUTILITY_API FBoxSphereBounds GetSphereBoundsFromCollisionShape(const FCollisionShape& CollisionShape, const FTransform& Transform);
}

UCLASS()
class MUTILITY_API UMPhysicsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "M|Physics", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static void DrawTraceHitResult(const UObject* WorldContextObject, const FHitResult& HitResult, const FMCollisionShapeRef& ShapeRef,
	                               const FQuat CollisionShapeRotation = FQuat(), const FLinearColor Color = FLinearColor::Red,
	                               const bool bPersistentLines = false, const float LifeTime = -1, const uint8 DepthPriority = 0,
	                               const float Thickness = 0);

	UFUNCTION(BlueprintCallable, Category = "M|Physics", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static bool LineTraceActor(const UObject* WorldContextObject, const FVector& Start, const FVector& End, ETraceTypeQuery TraceChannel,
	                           const AActor* ActorToTrace, FHitResult& OutHit);
};
