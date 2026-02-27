// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MGameplayCondition_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMOnConditionSourceChangedSignature);

/**
 * Base class for defining gameplay conditions
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class MUTILITY_API UMGameplayCondition_Base : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool Evaluate(const UObject* ContextObjectOverride = nullptr);

	UFUNCTION(BlueprintCallable)
	void ListenForChanges(const UObject* ContextObjectOverride = nullptr);

	UFUNCTION(BlueprintCallable)
	void StopListeningForChanges(const UObject* ContextObjectOverride = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString GetConditionDescriptionString() const;

	UPROPERTY(BlueprintAssignable)
	FMOnConditionSourceChangedSignature OnConditionSourceChangedDelegate;

protected:
	UFUNCTION(BlueprintNativeEvent)
	bool Evaluate_Impl(const UObject* ContextObject);
	
	UFUNCTION(BlueprintNativeEvent)
	void ListenForChanges_Impl(const UObject* ContextObject);
	
	UFUNCTION(BlueprintNativeEvent)
	void StopListeningForChanges_Impl(const UObject* ContextObject);
	
	UFUNCTION(BlueprintCallable)
	void BroadcastOnConditionSourceChanged();

	UPROPERTY(EditAnywhere, Category = "Condition")
	bool bInvertCondition = false;
	
	virtual const UObject* GetDefaultContextObject() const;
	const UObject* GetDefaultContextOrOverride(const UObject* ContextObjectOverride) const;
};
