// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"

namespace M::Debug
{
	UENUM()
	MUTILITY_API enum class EContextObjectLinkType
	{
		Direct, // MessageLog links to passed ContextObject directly. Makes sense for Actors generated dynamically
		Source // MessageLog links to the source asset of ContextObject. Makes sense for error related to Blueprint configuration
	};

	/**
	 * Common function for logging errors fixable by user configuration
	 * Always prints to console
	 * Additionally in the editor - adds a message to Message Log, displays notification with a button to quickly open Message Log
	 */
	MUTILITY_API void LogUserError(const FLogCategoryBase& LogCategory, const FString& ErrorStr, const UObject* ContextObject = nullptr,
	                               EContextObjectLinkType ContextObjectLinkType = EContextObjectLinkType::Direct);
}
