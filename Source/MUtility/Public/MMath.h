#pragma once

// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
struct MMath
{
	static FORCEINLINE_DEBUGGABLE FVector FromToVector(const FVector& From, const FVector& To)
	{
		const FVector Result = To - From;
		return Result;
	}

	static FORCEINLINE_DEBUGGABLE FVector FromToVectorNormalized(const FVector& From, const FVector& To)
	{
		FVector Result = FromToVector(From, To);
		Result.Normalize();
		return Result;
	}

	static FORCEINLINE_DEBUGGABLE float AngleBetweenSignedRad(const FVector2D& From, const FVector2D& To)
	{
		const float Dot = FVector2D::DotProduct(From, To);
		const float AngleRad = FMath::Atan2(From.X * To.Y - From.Y * To.X, Dot);

		return AngleRad;
	}

	static FORCEINLINE_DEBUGGABLE float AngleBetweenSignedDeg(const FVector2D& From, const FVector2D& To)
	{
		const float AngleRad = AngleBetweenSignedRad(From, To);
		const float AngleDeg = FMath::RadiansToDegrees(AngleRad);
		return AngleDeg;
	}

	static FORCEINLINE_DEBUGGABLE float AngleBetweenVectorsRad(const FVector& Vec1, const FVector& Vec2)
	{
		const float AngleRad = FMath::Acos(FMath::Clamp(FVector::DotProduct(Vec1.GetSafeNormal(), Vec2.GetSafeNormal()), -1.0f, 1.0f));
		return AngleRad;
	}

	static FORCEINLINE_DEBUGGABLE float AngleBetweenVectorsDeg(const FVector& Vec1, const FVector& Vec2)
	{
		const float AngleRad = AngleBetweenVectorsRad(Vec1, Vec2);
		const float AngleDeg = FMath::RadiansToDegrees(AngleRad);
		return AngleDeg;
	}

	static FORCEINLINE_DEBUGGABLE float SignedAngleBetweenVectorsRad(const FVector& Vec1, const FVector& Vec2)
	{
		const float AngleRad = AngleBetweenVectorsRad(Vec1, Vec2);
		const float Sign = FVector::CrossProduct(Vec1, Vec2).Z >= 0 ? 1.0f : -1.0f;

		const float SignedAngleRad = AngleRad * Sign;
		return SignedAngleRad;
	}

	static FORCEINLINE_DEBUGGABLE float SignedAngleBetweenVectorsDeg(const FVector& Vec1, const FVector& Vec2)
	{
		const float SignedAngleDeg = FMath::RadiansToDegrees(SignedAngleBetweenVectorsRad(Vec1, Vec2));
		return SignedAngleDeg;
	}

	static FORCEINLINE_DEBUGGABLE FVector ToHorizontalDirection(const FVector& Vector)
	{
		FVector Result = Vector;
		Result.Z = 0;
		Result.Normalize();

		return Result;
	}

	static FORCEINLINE_DEBUGGABLE FVector GetDirectorAlongSurfaceForDirection(const FVector& SurfaceNormal, const FVector& Direction)
	{
		const FVector SlideDirectionAlongSurface = FVector::VectorPlaneProject(Direction, SurfaceNormal.GetSafeNormal()).GetSafeNormal();
		return SlideDirectionAlongSurface;
	}

	/**
	 * Direction and TargetDirection are normalized inside the function
	 * If Direction equals zero DirectionTarget is returned
	 */
	static FORCEINLINE_DEBUGGABLE FVector RotateDirectionTowardsTargetDirectionByAngle(
		const FVector& Direction, const FVector& DirectionTarget, const float AngleDeg)
	{
		if (Direction.IsNearlyZero())
			return DirectionTarget.GetSafeNormal();

		const FVector DirectionNormalized = Direction.GetSafeNormal();
		const FVector DirectionTargetNormalized = DirectionTarget.GetSafeNormal();

		const float AngleBetweenDeg = SignedAngleBetweenVectorsDeg(DirectionNormalized, DirectionTargetNormalized);
		const float RotationAngleDeltaDeg = FMath::Sign(AngleBetweenDeg)
			* FMath::Min(AngleDeg, FMath::Abs(AngleBetweenDeg));

		FVector RotationAxis = FVector::CrossProduct(DirectionNormalized, DirectionTargetNormalized).GetAbs();
		RotationAxis.Normalize();

		const FQuat QuatRotation = FQuat(RotationAxis, FMath::DegreesToRadians(RotationAngleDeltaDeg));
		const FVector DirectionRotated = QuatRotation.RotateVector(DirectionNormalized);
		return DirectionRotated;
	}

	static FORCEINLINE_DEBUGGABLE FVector TranslateInputToControlRotationSpaceDirectionXY(
		const FVector2D& InputDirection, const FRotator& ControlRotation)
	{
		const float YawRad = FMath::DegreesToRadians(ControlRotation.Yaw);
		const float CosYaw = FMath::Cos(YawRad);
		const float SinYaw = FMath::Sin(YawRad);

		const FVector Direction(
			InputDirection.X * CosYaw - InputDirection.Y * SinYaw,
			InputDirection.X * SinYaw + InputDirection.Y * CosYaw,
			0
		);

		return Direction;
	}
};
