// Fill out your copyright notice in the Description page of Project Settings.


#include "MManualTimer.h"

bool FMManualTimer::Tick(float DeltaTime)
{
	CurrentTime = FMath::Min(CurrentTime + DeltaTime, Duration);
	const bool bCompleted = IsCompleted();
	if (bCompleted)
		CurrentTime = Duration;
	
	return bCompleted;
}

void FMManualTimer::Reset()
{
	CurrentTime = 0;
}

void FMManualTimer::Complete()
{
	CurrentTime = Duration;
}

float FMManualTimer::GetDuration() const
{
	return Duration;
}

void FMManualTimer::SetDuration(float DurationNew)
{
	Duration = DurationNew;
}

float FMManualTimer::GetProgressNormalized() const
{
	return CurrentTime / Duration;
}

float FMManualTimer::GetTimeLeft() const
{
	return Duration - CurrentTime;
}

float FMManualTimer::GetTimeElapsed() const
{
	return CurrentTime;
}

bool FMManualTimer::IsCompleted() const
{
	return FMath::IsNearlyEqual(CurrentTime, Duration);
}

void USRManualTimerLibrary::TickManualTimer(FMManualTimer& Timer, float DeltaTime)
{
	Timer.Tick(DeltaTime);
}

void USRManualTimerLibrary::ResetManualTimer(FMManualTimer& Timer)
{
	Timer.Reset();
}

void USRManualTimerLibrary::CompleteManualTimer(FMManualTimer& Timer)
{
	Timer.Complete();
}

void USRManualTimerLibrary::SetManualTimerDuration(FMManualTimer& Timer, float DurationNew)
{
	Timer.SetDuration(DurationNew);
}

float USRManualTimerLibrary::GetManualTimerProgressNormalized(FMManualTimer Timer)
{
	return Timer.GetProgressNormalized();
}

float USRManualTimerLibrary::GetManualTimerTimeLeft(FMManualTimer Timer)
{
	return Timer.GetTimeLeft();
}

float USRManualTimerLibrary::GetManualTimerTimeElapsed(FMManualTimer Timer)
{
	return Timer.GetTimeElapsed();
}

bool USRManualTimerLibrary::IsManualTimerCompleted(FMManualTimer Timer)
{
	return Timer.IsCompleted();
}
