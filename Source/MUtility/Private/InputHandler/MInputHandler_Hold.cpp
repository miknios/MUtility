// Fill out your copyright notice in the Description page of Project Settings.


#include "InputHandler/MInputHandler_Hold.h"

void UMInputHandler_Hold::SetInputHeld(const bool bInInputHeld, const bool bControlledStateCurrent)
{
	if (bAwaitsInputUp)
	{
		if (bInInputHeld)
		{
			bAwaitsInputUp = false;
		}
	}

	bInputHeldOld = bInputHeld;
	bInputHeld = bInInputHeld;

	if (!bAwaitsInputUp)
	{
		if (bInputHeld != bInputHeldOld)
		{
			const bool StateToSet = bInputHeld;
			OnInputHandlerUpdateDelegate.Broadcast(StateToSet);
		}
	}
}

void UMInputHandler_Hold::SetControlledStateChangedExternally(bool bStateNew)
{
	// If something set controlled state to false, but player is still holding the button, wait for the input up before we can activate it with input again
	if (!bStateNew && bInputHeld)
		bAwaitsInputUp = true;
}
