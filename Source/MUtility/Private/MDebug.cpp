// Copyright (c) Miknios. All rights reserved.

#include "MDebug.h"

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#include "MessageLogModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

namespace M::Debug::Private
{
#if WITH_EDITOR
	inline TSharedPtr<SNotificationItem> ErrorNotificationActive;
	inline TArray<FString> ErrorNotificationsToDisplayArray;
#endif

	FString ConstructNotificationErrorString()
	{
		TStringBuilder<1024> StringBuilder;
		for (int i = 0; i < ErrorNotificationsToDisplayArray.Num(); ++i)
		{
			StringBuilder << ErrorNotificationsToDisplayArray[i];

			if (i < ErrorNotificationsToDisplayArray.Num() - 1)
			{
				StringBuilder << "\n\n";
			}
		}

		FString Result = StringBuilder.ToString();
		return Result;
	}
}

void M::Debug::LogUserError(const FLogCategoryBase& LogCategory, const FString& ErrorStr, const UObject* ContextObject,
                            EContextObjectLinkType ContextObjectLinkType)
{
#if WITH_EDITOR
	const FName LogCategoryName = LogCategory.GetCategoryName();

	// Add log to Message Log
	TSharedRef<FTokenizedMessage> TokenizedMessage = FMessageLog(LogCategoryName)
	                                                 .SuppressLoggingToOutputLog()
	                                                 // suppressing because logging is done independently, so it's universal for editor and build
	                                                 .Error()
	                                                 ->AddToken(FTextToken::Create(
		                                                 FText::FromString(ErrorStr)));

	if (IsValid(ContextObject))
	{
		const UObject* ObjectToLink = ContextObjectLinkType == EContextObjectLinkType::Direct
			                              ? ContextObject
			                              : ContextObject->GetClass()->ClassGeneratedBy;
		TokenizedMessage->AddToken(FUObjectToken::Create(ObjectToLink));
	}

	const TSharedPtr<SNotificationItem> ErrorNotification = Private::ErrorNotificationActive;
	if (!ErrorNotification.IsValid() || ErrorNotification->GetCompletionState() == SNotificationItem::CS_Success)
	{
		// Add notification
		FNotificationInfo Info(FText::FromString(TEXT("Error occured")));
		Info.SubText = FText::FromString(ErrorStr);
		Info.bUseCopyToClipboard = true;
		Info.bFireAndForget = false;
		Info.bUseThrobber = false;
		Info.ExpireDuration = 0;
		Info.FadeInDuration = 0.1f;
		Info.FadeOutDuration = 0.1f;

		FNotificationButtonInfo OpenMessageLogButtonInfo =
			FNotificationButtonInfo(FText::FromString(TEXT("Open Message Log")),
			                        FText::FromString(TEXT("")),
			                        FSimpleDelegate::CreateLambda([LogCategoryName]
			                        {
				                        FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<
					                        FMessageLogModule>("MessageLog");
				                        MessageLogModule.OpenMessageLog(LogCategoryName);

				                        if (Private::ErrorNotificationActive.IsValid())
				                        {
					                        Private::ErrorNotificationActive->ExpireAndFadeout();
					                        Private::ErrorNotificationActive->SetCompletionState(SNotificationItem::CS_Success);
					                        Private::ErrorNotificationActive.Reset();
				                        }
			                        }), SNotificationItem::CS_None);

		FNotificationButtonInfo CloseNotificationButtonInfo =
			FNotificationButtonInfo(FText::FromString(TEXT("Close")),
			                        FText::FromString(TEXT("")),
			                        FSimpleDelegate::CreateLambda([]
			                        {
				                        if (Private::ErrorNotificationActive.IsValid())
				                        {
					                        Private::ErrorNotificationActive->ExpireAndFadeout();
					                        Private::ErrorNotificationActive->SetCompletionState(SNotificationItem::CS_Success);
					                        Private::ErrorNotificationActive.Reset();
				                        }
			                        }), SNotificationItem::CS_None);

		Info.ButtonDetails.Add(MoveTemp(OpenMessageLogButtonInfo));
		Info.ButtonDetails.Add(MoveTemp(CloseNotificationButtonInfo));

		Private::ErrorNotificationActive = FSlateNotificationManager::Get().AddNotification(Info);

		Private::ErrorNotificationsToDisplayArray.Empty();
		Private::ErrorNotificationsToDisplayArray.Emplace(ErrorStr);
	}
	else
	{
		ErrorNotification->Pulse(FLinearColor::Red);

		Private::ErrorNotificationsToDisplayArray.Emplace(ErrorStr);
		if (Private::ErrorNotificationsToDisplayArray.Num() > 10)
		{
			Private::ErrorNotificationsToDisplayArray.RemoveAt(0);
		}

		ErrorNotification->SetText(FText::FromString(FString::Printf(TEXT("Error occured (%d)"),
		                                                             Private::ErrorNotificationsToDisplayArray.Num())));

		ErrorNotification->SetSubText(FText::FromString(Private::ConstructNotificationErrorString()));
	}
#endif

	// Log to console
	const TCHAR* const LogColor = FMessageLog::GetLogColor(EMessageSeverity::Error);
	if (LogColor)
	{
		SET_WARN_COLOR(LogColor);
	}

	FMsg::Logf(__FILE__, __LINE__, LogCategory.GetCategoryName(), FMessageLog::GetLogVerbosity(EMessageSeverity::Error),
	           TEXT("%s"), *ErrorStr);

	CLEAR_WARN_COLOR();
}
