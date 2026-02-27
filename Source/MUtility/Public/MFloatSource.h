// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MFloatSource.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMFloatSourceChangedSignature);

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class MUTILITY_API UMFloatSource_Base : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float GetFloatValue(const UObject* ContextObjectOverride = nullptr) const;
	
	UFUNCTION(BlueprintCallable)
	void ListenForChanges(const UObject* ContextObjectOverride = nullptr);
	
	UFUNCTION(BlueprintCallable)
	void StopListeningForChanges(const UObject* ContextObjectOverride = nullptr);

	UPROPERTY(BlueprintAssignable)
	FMFloatSourceChangedSignature OnValueChangedDelegate;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetFloatValue_Impl(const UObject* ContextObject) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ListenForChanges_Impl(const UObject* ContextObject);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopListeningForChanges_Impl(const UObject* ContextObject );
	
	UFUNCTION(BlueprintCallable)
	void BroadcastOnValueChanged();
	
	virtual const UObject* GetDefaultContextObject() const;
	const UObject* GetDefaultContextOrOverride(const UObject* ContextObjectOverride) const;
};

UCLASS(NotBlueprintable, DisplayName = "Static Value")
class UMFloatSource_Static : public UMFloatSource_Base
{
	GENERATED_BODY()

public:
	// UMFloatSource_Base
	virtual float GetFloatValue_Impl_Implementation(const UObject* ContextObject) const override;
	// ~ UMFloatSource_Base

protected:
	UPROPERTY(EditAnywhere)
	float FloatValue = 0;
};

// TODO: finish this - implement different child classes for add/subtract/multiply/divide
UCLASS(Abstract)
class UMFloatSource_Operation : public UMFloatSource_Base
{
	GENERATED_BODY()
};
