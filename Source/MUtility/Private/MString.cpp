// Fill out your copyright notice in the Description page of Project Settings.


#include "MString.h"

FString UMString::ToString(const bool Value)
{
	return Value ? TEXT("true") : TEXT("false");
}
