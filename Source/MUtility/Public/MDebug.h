// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MDebug.generated.h"

UENUM()
enum class EMDebug_ContextObjectLinkType : uint8
{
	Direct, // MessageLog links to passed ContextObject directly. Makes sense for Actors generated dynamically
	Source // MessageLog links to the source asset of ContextObject. Makes sense for error related to Blueprint configuration
};

namespace M::Debug
{
#if WITH_EDITOR
	MUTILITY_API UObject* TryGetEditorCounterpartObject(const UObject& Object);
#endif
	
	/**
	 * Common function for logging errors fixable by user configuration
	 * Always prints to console
	 * Additionally in the editor - adds a message to Message Log, displays notification with a button to quickly open Message Log
	 */
	MUTILITY_API void LogUserError(const FLogCategoryBase& LogCategory, const FString& ErrorStr, const UObject* ContextObject = nullptr,
	                               EMDebug_ContextObjectLinkType ContextObjectLinkType = EMDebug_ContextObjectLinkType::Source);
}

UCLASS()
class UMDebugLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// TODO: make a version of this function where we allow to pass a log category
	//		currently there is a problem because we require LogCategory to be of type FLogCategoryBase which can't be made from FName
	UFUNCTION(BlueprintCallable)
	static void LogUserError(const FString& ErrorStr, UObject* ContextObject = nullptr,
	                         EMDebug_ContextObjectLinkType ContextObjectLinkType = EMDebug_ContextObjectLinkType::Source);
};
