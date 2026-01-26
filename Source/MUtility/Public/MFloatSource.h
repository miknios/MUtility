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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetFloatValue(UObject* ContextObject = nullptr) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ListenForChanges();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopListeningForChanges();

	UPROPERTY(BlueprintAssignable)
	FMFloatSourceChangedSignature OnValueChangedDelegate;

protected:
	UFUNCTION(BlueprintCallable)
	void BroadcastOnValueChanged();
};

UCLASS(NotBlueprintable, DisplayName = "Static Value")
class UMFloatSource_Static : public UMFloatSource_Base
{
	GENERATED_BODY()

public:
	// UMFloatSource_Base
	virtual float GetFloatValue_Implementation(UObject* ContextObject) const override;
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
