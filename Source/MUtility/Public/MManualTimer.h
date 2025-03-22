// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MManualTimer.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct MUTILITY_API FMManualTimer
{
	GENERATED_BODY()

	FMManualTimer() = default;

	FMManualTimer(float Duration)
		: Duration(Duration)
	{
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 0;

public:
	// Returns true if timer has completed in this tick
	bool Tick(float DeltaTime);

	void Reset();

	void Complete();

	float GetDuration() const;

	void SetDuration(float DurationNew);

	float GetProgressNormalized() const;

	float GetTimeLeft() const;

	float GetTimeElapsed() const;

	bool IsCompleted() const;
};

UCLASS()
class USRManualTimerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void TickManualTimer(UPARAM(ref) FMManualTimer& Timer, float DeltaTime);

	UFUNCTION(BlueprintCallable)
	static void ResetManualTimer(UPARAM(ref) FMManualTimer& Timer);

	UFUNCTION(BlueprintCallable)
	static void CompleteManualTimer(UPARAM(ref) FMManualTimer& Timer);

	UFUNCTION(BlueprintCallable)
	static void SetManualTimerDuration(UPARAM(ref) FMManualTimer& Timer, float DurationNew);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetManualTimerProgressNormalized(FMManualTimer Timer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetManualTimerTimeLeft(FMManualTimer Timer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetManualTimerTimeElapsed(FMManualTimer Timer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsManualTimerCompleted(FMManualTimer Timer);
};
