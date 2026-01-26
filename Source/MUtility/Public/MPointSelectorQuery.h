// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Team/MTeamTypes.h"

#include "MPointSelectorQuery.generated.h"

class UMPointSelectorQueryFilter_Base;
class UMPointSelectorQueryFactor_Base;

UINTERFACE()
class UMSelectorQueryPointInterface : public UInterface
{
	GENERATED_BODY()
};

class MUTILITY_API IMSelectorQueryPointInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetLookAtLocation() const;

	// Returns value between 0-1 that informs how important is that specific look at point in comparison to others
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetImportanceValue() const;
};

UCLASS()
class UMSelectorQueryPoint_ImportanceValueAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float ImportanceValue = 1;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMSelectorQueryPoint_GenericSphere : public USphereComponent, public IMSelectorQueryPointInterface
{
	GENERATED_BODY()

public:
	// IMSelectorQueryPointInterface
	virtual FVector GetLookAtLocation_Implementation() const override;
	virtual float GetImportanceValue_Implementation() const override;
	// ~ IMSelectorQueryPointInterface

	UFUNCTION(BlueprintCallable)
	void SetImportanceValue(const float NewImportanceValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMSelectorQueryPoint_ImportanceValueAsset> ImportanceValueAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "ImportanceValueAsset == nullptr"))
	float ImportanceValue = 1;
};

USTRUCT(BlueprintType)
struct FMPointSelectorFactorConfigEntryData
{
	GENERATED_BODY()

	// How important is this factor in look at point calculation logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 1;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UMPointSelectorQueryFactor_Base* Selector = nullptr;
};

UCLASS()
class UMPointSelectorQuerySettingsAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMPointSelectorFactorConfigEntryData> SelectorFactorConfigs;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMPointSelectorQueryFilter_Base>> Filters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceMax = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AngleMax = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LookAtPointSelectionOverlapProfileName;
};

UCLASS(Abstract, BLueprintable, DefaultToInstanced, EditInlineNew)
class MUTILITY_API UMPointSelectorQueryFilter_Base : public UObject
{
	GENERATED_BODY()

public:
	bool FilterPoint(const UObject* ContextObject,
	                 const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                 const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Point Selector Query")
	bool FilterPoint_Impl(const UObject* ContextObject,
	                      const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                      const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const;

	UPROPERTY(EditAnywhere, Category = "Filter")
	bool bInvert = false;
};

UCLASS(DisplayName = "Team Affiliation")
class UMPointSelectorQueryFilter_TeamAffiliation : public UMPointSelectorQueryFilter_Base
{
	GENERATED_BODY()

public:
	// UMPointSelectorQueryFilter_Base
	virtual bool FilterPoint_Impl_Implementation(const UObject* ContextObject,
	                                             const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                                             const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) const override;
	// ~ UMPointSelectorQueryFilter_Base

protected:
	UPROPERTY(EditAnywhere, Category = "Filter")
	FMTeamAffiliationFilter TeamAffiliationFilter;
};

UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class MUTILITY_API UMPointSelectorQueryFactor_Base : public UObject
{
	GENERATED_BODY()

public:
	// Returns value between 0-1 that influence selecting given LookAtPoint as a point we look at
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Point Selector Query")
	float CalculateFactorValueForLookAtPoint(const UObject* ContextObject,
	                                         const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                                         const UMPointSelectorQuerySettingsAsset* QuerySettings,
	                                         const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint);
};

UCLASS(DisplayName = "Distance")
class UMPointSelectorQueryFactor_Distance : public UMPointSelectorQueryFactor_Base
{
	GENERATED_BODY()

public:
	virtual float CalculateFactorValueForLookAtPoint_Implementation(
		const UObject* ContextObject, const FVector& ReferenceLocation,
		const FVector& ReferenceDirection,
		const UMPointSelectorQuerySettingsAsset* QuerySettings,
		const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) override;
};

UCLASS(DisplayName = "Angle")
class UMPointSelectorQueryFactor_Angle : public UMPointSelectorQueryFactor_Base
{
	GENERATED_BODY()

public:
	virtual float CalculateFactorValueForLookAtPoint_Implementation(
		const UObject* ContextObject, const FVector& ReferenceLocation,
		const FVector& ReferenceDirection,
		const UMPointSelectorQuerySettingsAsset* QuerySettings,
		const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) override;
};

UCLASS(DisplayName = "POI Importance")
class UMPointSelectorQueryFactor_PointImportance : public UMPointSelectorQueryFactor_Base
{
	GENERATED_BODY()

public:
	virtual float CalculateFactorValueForLookAtPoint_Implementation(
		const UObject* ContextObject, const FVector& ReferenceLocation,
		const FVector& ReferenceDirection,
		const UMPointSelectorQuerySettingsAsset* QuerySettings,
		const TScriptInterface<IMSelectorQueryPointInterface>& LookAtPoint) override;
};

UCLASS()
class MUTILITY_API UMPointSelectorQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool PointSelectorQuery(const UObject* WorldContextObject,
	                               const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                               UMPointSelectorQuerySettingsAsset* SettingsAsset,
	                               FCollisionQueryParams QueryParams, TScriptInterface<IMSelectorQueryPointInterface>& OutLookAtPoint);

	UFUNCTION(BlueprintCallable, Category = "Collision", DisplayName = "Point Selector Query",
		meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore"))
	static bool BP_PointSelectorQuery(const UObject* WorldContextObject,
	                                  const FVector& ReferenceLocation, const FVector& ReferenceDirection,
	                                  UMPointSelectorQuerySettingsAsset* SettingsAsset,
	                                  const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf,
	                                  TScriptInterface<IMSelectorQueryPointInterface>& OutLookAtPoint);
};
