// Copyright (c) Miknios. All rights reserved.


#include "MPointSelectorQuery.h"

#include "KismetTraceUtils.h"
#include "MDebug.h"
#include "MMath.h"
#include "Engine/OverlapResult.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Team/MTeamLibrary.h"

float UMPointSelectorQueryFactor_Base::CalculateFactorValueForLookAtPoint_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const UMPointSelectorQuerySettingsAsset* QuerySettings,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint)
{
	return 0.f;
}

FVector UMSelectorQueryPoint_GenericSphere::GetLookAtLocation_Implementation() const
{
	return GetComponentLocation();
}

float UMSelectorQueryPoint_GenericSphere::GetImportanceValue_Implementation() const
{
	if (ImportanceValueAsset != nullptr)
	{
		return ImportanceValueAsset->ImportanceValue;
	}

	return ImportanceValue;
}

void UMSelectorQueryPoint_GenericSphere::SetImportanceValue(const float NewImportanceValue)
{
	ImportanceValue = NewImportanceValue;
}

bool UMPointSelectorQueryFilter_Base::FilterPoint_Impl_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const
{
	return true;
}

bool UMPointSelectorQueryFilter_Base::FilterPoint(const UObject* ContextObject, const FVector& ReferenceLocation,
                                                  const FVector& ReferenceDirection,
                                                  const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const
{
	const bool FilterResult = FilterPoint_Impl(ContextObject, ReferenceLocation, ReferenceDirection, LookAtPoint);
	return bInvert ? !FilterResult : FilterResult;
}

bool UMPointSelectorQueryFilter_TeamAffiliation::FilterPoint_Impl_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const
{
	const AActor* LookAtPointActorOwner;
	if (const UActorComponent* LookAtPointComponent = Cast<UActorComponent>(LookAtPoint.GetObject()))
	{
		LookAtPointActorOwner = LookAtPointComponent->GetOwner();
	}
	else
	{
		LookAtPointActorOwner = Cast<AActor>(LookAtPoint.GetObject());
	}

	if (LookAtPointActorOwner == nullptr)
	{
		return false;
	}

	const AActor* ContextActor;
	if (const UActorComponent* ContextComponent = Cast<UActorComponent>(ContextObject))
	{
		ContextActor = ContextComponent->GetOwner();
	}
	else
	{
		ContextActor = Cast<AActor>(ContextObject);
	}

	if (ContextActor == nullptr)
	{
		return false;
	}

	const bool FilterResult = UMTeamLibrary::EvaluateAffiliationFilterForActors(TeamAffiliationFilter, LookAtPointActorOwner, ContextActor);
	return FilterResult;
}

float UMPointSelectorQueryFactor_Distance::CalculateFactorValueForLookAtPoint_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const UMPointSelectorQuerySettingsAsset* QuerySettings,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint)
{
	if (QuerySettings == nullptr)
	{
		return 0.f;
	}

	const FVector LookAtTo = LookAtPoint->Execute_GetLookAtLocation(LookAtPoint.GetObject());
	const float Distance = FVector::Distance(ReferenceLocation, LookAtTo);
	const float DistanceMax = QuerySettings->DistanceMax;
	const float Result = 1 - FMath::Clamp(Distance / DistanceMax, 0, 1);
	return Result;
}

float UMPointSelectorQueryFactor_Angle::CalculateFactorValueForLookAtPoint_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const UMPointSelectorQuerySettingsAsset* QuerySettings,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint)
{
	if (QuerySettings == nullptr)
	{
		return 0.f;
	}

	const FVector ToLookAtPointVector =
		MMath::FromToVector(ReferenceDirection,
		                    LookAtPoint->Execute_GetLookAtLocation(LookAtPoint.GetObject()));
	const float Dot = FVector::DotProduct(ReferenceDirection, ToLookAtPointVector);
	const float Result = FMath::Clamp(Dot, 0, 1);
	return Result;
}

float UMPointSelectorQueryFactor_PointImportance::CalculateFactorValueForLookAtPoint_Implementation(
	const UObject* ContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	const UMPointSelectorQuerySettingsAsset* QuerySettings,
	const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint)
{
	return LookAtPoint->Execute_GetImportanceValue(LookAtPoint.GetObject());
}

bool UMPointSelectorQueryLibrary::PointSelectorQuery(const UObject* WorldContextObject, const FVector& ReferenceLocation,
                                                     const FVector& ReferenceDirection, UMPointSelectorQuerySettingsAsset* SettingsAsset,
                                                     FCollisionQueryParams QueryParams,
                                                     TScriptInterface<IMSelectorQueryPointInterface>& OutLookAtPoint)
{
	if (WorldContextObject == nullptr)
	{
		M::Debug::LogUserError(LogTemp, TEXT("Can't query point because WorldContextObject is null"), WorldContextObject);
		return false;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (World == nullptr)
	{
		return false;
	}

	if (SettingsAsset == nullptr)
	{
		M::Debug::LogUserError(LogTemp, TEXT("Can't query point because SettingsAsset is null"), WorldContextObject);
		return false;
	}

	const FVector OverlapPos = ReferenceLocation;
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SettingsAsset->DistanceMax);

	TArray<FOverlapResult> OverlapResults;
	World->OverlapMultiByProfile(OverlapResults, OverlapPos, FQuat::Identity,
	                             SettingsAsset->LookAtPointSelectionOverlapProfileName,
	                             CollisionShape, QueryParams);

	float ScoreBest = -1;
	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		UPrimitiveComponent* PrimitiveHit = OverlapResult.GetComponent();
		if (!PrimitiveHit->Implements<UMSelectorQueryPointInterface>())
		{
			continue;
		}

		TScriptInterface<IMSelectorQueryPointInterface> LookAtPoint = TScriptInterface<IMSelectorQueryPointInterface>(PrimitiveHit);

		const float Distance = FVector::Distance(OverlapPos, LookAtPoint->Execute_GetLookAtLocation(LookAtPoint.GetObject()));
		if (Distance > SettingsAsset->DistanceMax)
		{
			continue;
		}

		const FVector ToLookAtPointVector = MMath::FromToVector(ReferenceLocation,
		                                                        LookAtPoint->Execute_GetLookAtLocation(LookAtPoint.GetObject()));
		const float Angle = MMath::AngleBetweenVectorsDeg(ReferenceDirection, ToLookAtPointVector);
		if (Angle > SettingsAsset->AngleMax)
		{
			continue;
		}

		bool bAllFiltersPassed = true;
		for (const UMPointSelectorQueryFilter_Base* QueryFilter : SettingsAsset->Filters)
		{
			if (QueryFilter == nullptr)
			{
				continue;
			}

			const bool FilterPassed = QueryFilter->FilterPoint(WorldContextObject, ReferenceLocation, ReferenceDirection, LookAtPoint);
			bAllFiltersPassed &= FilterPassed;

			if (!FilterPassed)
			{
				break;
			}
		}

		if (!bAllFiltersPassed)
		{
			continue;
		}

		float Score = 0;
		for (const FMPointSelectorFactorConfigEntryData& FactorConfig : SettingsAsset->SelectorFactorConfigs)
		{
			if (FactorConfig.Selector == nullptr)
			{
				M::Debug::LogUserError(LogTemp,
				                       TEXT("Can't apply selector factor to score because SelectorFactorConfig.Selector is null"),
				                       SettingsAsset);
				continue;
			}

			const float FactorValue = FactorConfig.Selector->CalculateFactorValueForLookAtPoint(
				WorldContextObject, ReferenceLocation, ReferenceDirection, SettingsAsset, LookAtPoint);
			Score += FactorValue * FactorConfig.Weight;
		}

		UE_VLOG_SPHERE(WorldContextObject, LogTemp, Display, LookAtPoint->Execute_GetLookAtLocation(LookAtPoint.GetObject()), 10.f,
		               FColor::Green, TEXT("%.2f"), Score);

		if (Score > ScoreBest)
		{
			ScoreBest = Score;
			OutLookAtPoint = MoveTemp(LookAtPoint);
		}
	}

	return ScoreBest > -1;
}

bool UMPointSelectorQueryLibrary::BP_PointSelectorQuery(
	const UObject* WorldContextObject,
	const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	UMPointSelectorQuerySettingsAsset* SettingsAsset,
	const TArray<AActor*>& ActorsToIgnore, const bool bIgnoreSelf,
	TScriptInterface<IMSelectorQueryPointInterface>& OutLookAtPoint)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);
	Params.bTraceComplex = false;

	if (bIgnoreSelf)
	{
		const AActor* IgnoreActor = Cast<AActor>(WorldContextObject);
		if (IgnoreActor)
		{
			Params.AddIgnoredActor(IgnoreActor);
		}
		else
		{
			// find owner
			const UObject* CurrentObject = WorldContextObject;
			while (CurrentObject)
			{
				CurrentObject = CurrentObject->GetOuter();
				IgnoreActor = Cast<AActor>(CurrentObject);
				if (IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
					break;
				}
			}
		}
	}

	const bool Result = PointSelectorQuery(WorldContextObject, ReferenceLocation, ReferenceDirection, SettingsAsset, Params,
	                                       OutLookAtPoint);
	return Result;
}
