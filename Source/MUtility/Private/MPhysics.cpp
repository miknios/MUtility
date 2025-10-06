// Copyright (c) Miknios. All rights reserved.


#include "MPhysics.h"

#include "CollisionShape.h"
#include "DrawDebugHelpers.h"

FCollisionShape M::Physics::MakeCollisionShapeFromShapeRef(const FMCollisionShapeRef& ShapeRef)
{
	switch (ShapeRef.ShapeType)
	{
	case EMCollisionShape::Box:
		{
			const FCollisionShape CollisionShape = FCollisionShape::MakeBox(ShapeRef.BoxExtent / 2.f);
			return CollisionShape;
		}
	case EMCollisionShape::Sphere:
		{
			const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(ShapeRef.SphereRadius);
			return CollisionShape;
		}
	case EMCollisionShape::Capsule:
		{
			const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(ShapeRef.CapsuleRadius, ShapeRef.CapsuleHalfHeight);
			return CollisionShape;
		}
	case EMCollisionShape::Line:
		{
			return FCollisionShape();
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Unknown Collision Shape Type"));
	return FCollisionShape();
}

FMCollisionShapeRef M::Physics::MakeCollisionShapeRefFromCollisionShape(const FCollisionShape& Shape)
{
	FMCollisionShapeRef ShapeRef;

	switch (Shape.ShapeType)
	{
	case ECollisionShape::Box:
		{
			ShapeRef.ShapeType = EMCollisionShape::Box;
			ShapeRef.BoxExtent = Shape.GetBox() * 2.f;
		}
	case ECollisionShape::Sphere:
		{
			ShapeRef.ShapeType = EMCollisionShape::Sphere;
			ShapeRef.SphereRadius = Shape.GetSphereRadius();
		}
	case ECollisionShape::Capsule:
		{
			ShapeRef.ShapeType = EMCollisionShape::Capsule;
			ShapeRef.CapsuleRadius = Shape.GetCapsuleRadius();
			ShapeRef.CapsuleHalfHeight = Shape.GetCapsuleHalfHeight();
		}
	case ECollisionShape::Line:
		{
			ShapeRef.ShapeType = EMCollisionShape::Line;
		}
	}

	return ShapeRef;
}

void M::Physics::DrawCollisionShape(const UWorld* World, const FCollisionShape& CollisionShape, const FTransform& Transform,
                                    const FColor& Color, const bool bPersistentLines, const float LifeTime, const uint8 DepthPriority,
                                    const float Thickness)
{
	constexpr int32 SphereSegments = 8;

	if (!IsValid(World))
	{
		return;
	}

	switch (CollisionShape.ShapeType)
	{
	case ECollisionShape::Box:
		DrawDebugBox(World, Transform.GetLocation(), CollisionShape.GetBox() * 2.f, Transform.GetRotation(), Color, bPersistentLines,
		             LifeTime,
		             DepthPriority, Thickness);
		break;
	case ECollisionShape::Sphere:
		DrawDebugSphere(World, Transform.GetLocation(), CollisionShape.GetSphereRadius(), SphereSegments, Color, bPersistentLines, LifeTime,
		                DepthPriority, Thickness);
		break;
	case ECollisionShape::Capsule:
		DrawDebugCapsule(World, Transform.GetLocation(), CollisionShape.GetCapsuleHalfHeight(), CollisionShape.GetCapsuleRadius(),
		                 Transform.GetRotation(), Color,
		                 bPersistentLines, LifeTime, DepthPriority, Thickness);
		break;
	case ECollisionShape::Line:
		DrawDebugPoint(World, Transform.GetLocation(), 10.0f, Color, bPersistentLines, LifeTime, DepthPriority);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Shape Type not handled by M::Physics::DrawCollisionShape"));
	}
}

// TODO: think about adding more optional data to draw here (surface normal?)
void M::Physics::DrawTraceHitResult(const UWorld* World, const FHitResult& HitResult, const FCollisionShape& CollisionShape,
                                    const FQuat& CollisionShapeRotation, const FColor& Color, bool bPersistentLines, const float LifeTime,
                                    const uint8 DepthPriority, const float Thickness)
{
	if (!IsValid(World))
	{
		return;
	}

	// Draw trace line (start -> impact point or end if no hit)
	const FVector& Start = HitResult.TraceStart;
	const FVector& End = HitResult.bBlockingHit ? HitResult.Location : HitResult.TraceEnd;

	DrawDebugLine(World, Start, End, Color, false, LifeTime, 0, Thickness);

	DrawCollisionShape(World, CollisionShape, FTransform(CollisionShapeRotation, End),
	                   Color, bPersistentLines, LifeTime, DepthPriority, Thickness);

	// If there was a blocking hit, draw impact point
	if (HitResult.bBlockingHit)
	{
		// Impact point
		DrawDebugSphere(World, HitResult.ImpactPoint, 8.0f, 12, Color, false, LifeTime);

		// Small text with hit actor name (optional)
		if (const AActor* HitActor = HitResult.GetActor())
		{
			DrawDebugString(
				World,
				HitResult.ImpactPoint + FVector(0, 0, 20),
				HitActor->GetName(),
				nullptr,
				FColor::White,
				LifeTime
			);
		}
	}
	else
	{
		// No hit → mark trace end
		DrawDebugSphere(World, HitResult.TraceEnd, 6.0f, 8, FColor::Yellow, bPersistentLines, LifeTime, DepthPriority, Thickness);
		DrawDebugString(World, HitResult.TraceEnd + FVector(0, 0, 20), TEXT("NO HIT"), nullptr, FColor::Yellow, LifeTime);
	}
}

void UMPhysicsBlueprintLibrary::DrawTraceHitResult(const UObject* WorldContextObject, const FHitResult& HitResult,
                                                   const FMCollisionShapeRef& ShapeRef, const FQuat CollisionShapeRotation,
                                                   const FLinearColor Color, const bool bPersistentLines,
                                                   const float LifeTime, const uint8 DepthPriority, const float Thickness)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	M::Physics::DrawTraceHitResult(World, HitResult, M::Physics::MakeCollisionShapeFromShapeRef(ShapeRef), CollisionShapeRotation,
	                               Color.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);
}
