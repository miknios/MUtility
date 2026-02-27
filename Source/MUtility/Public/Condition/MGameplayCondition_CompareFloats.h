// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameplayCondition_Base.h"
#include "MGameplayCondition_CompareFloats.generated.h"

class UMFloatSource_Base;

UENUM(BlueprintType)
enum class EMCompareOp : uint8
{
	Less,
	LessOrEqual,
	Equal,
	NotEqual,
	GreaterOrEqual,
	Greater
};

UCLASS(DisplayName = "Compare Floats")
class MUTILITY_API UMGameplayCondition_CompareFloats : public UMGameplayCondition_Base
{
	GENERATED_BODY()
	
public:
	// UMGameplayCondition_Base
	virtual bool Evaluate_Impl_Implementation(const UObject* ContextObject) override;
	virtual void ListenForChanges_Impl_Implementation(const UObject* ContextObject) override;
	virtual void StopListeningForChanges_Impl_Implementation(const UObject* ContextObject) override;
	virtual FString GetConditionDescriptionString_Implementation() const override;
	// ~ UMGameplayCondition_Base

protected:
	bool CompareFloats(const float ValueLeft, const float ValueRight) const;
	
	UFUNCTION()
	void OnFloatValueChanged();
	
	UPROPERTY(Instanced, EditAnywhere, Category = "Condition")
	TObjectPtr<UMFloatSource_Base> ValueSourceLeft;

	UPROPERTY(EditAnywhere, Category = "Condition")
	EMCompareOp CompareOp;

	UPROPERTY(Instanced, EditAnywhere, Category = "Condition")
	TObjectPtr<UMFloatSource_Base> ValueSourceRight;
};
