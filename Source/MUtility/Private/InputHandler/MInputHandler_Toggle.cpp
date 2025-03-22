// Fill out your copyright notice in the Description page of Project Settings.


#include "InputHandler/MInputHandler_Toggle.h"

void UMInputHandler_Toggle::SetInputHeld(const bool bInInputHeld, const bool bControlledStateCurrent)
{
	bInputHeldOld = bInputHeld;
	bInputHeld = bInInputHeld;
	
	if (bInputHeld && !bInputHeldOld)
	{
		const bool StateToSet = !bControlledStateCurrent;
		OnInputHandlerUpdateDelegate.Broadcast(StateToSet);
	}
}
