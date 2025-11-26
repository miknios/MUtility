// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameplayCondition_Base.h"
#include "MGameplayCondition_Compositor.generated.h"

UENUM(BlueprintType)
enum class EMConditionCompositionType : uint8
{
	AND,
	OR
};

/**
 * Condition that allows chaining multiple conditions with each other with AND or OR
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Compositor"))
class MUTILITY_API UMGameplayCondition_Compositor : public UMGameplayCondition_Base
{
	GENERATED_BODY()

public:
	// ~ UWestCondition_Base
	virtual bool Evaluate_Impl_Implementation(const UWorld* World) override;
	virtual void ListenForChanges_Implementation(const UWorld* World) override;
	virtual void StopListeningForChanges_Implementation(const UWorld* World) override;
	virtual FString GetConditionDescriptionString_Implementation() const override;
	// ~ UWestCondition_Base

protected:
	UFUNCTION()
	void OnInternalConditionChanged();

	UPROPERTY(Instanced, EditAnywhere)
	TArray<TObjectPtr<UMGameplayCondition_Base>> Conditions;

	UPROPERTY(EditAnywhere)
	EMConditionCompositionType CompositionType;
};
