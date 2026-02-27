// Copyright (c) Miknios. All rights reserved.


#include "Condition/MGameplayCondition_CompareFloats.h"

#include "MFloatSource.h"

bool UMGameplayCondition_CompareFloats::Evaluate_Impl_Implementation(const UObject* ContextObject)
{
	if (!ensureAlways(ValueSourceLeft != nullptr && ValueSourceRight != nullptr))
	{
		return false;
	}

	const float ValueLeftEvaluated = ValueSourceLeft->GetFloatValue(ContextObject);
	const float ValueRightEvaluated = ValueSourceRight->GetFloatValue(ContextObject);
	const bool bResult = CompareFloats(ValueLeftEvaluated, ValueRightEvaluated);

	return bResult;
}

void UMGameplayCondition_CompareFloats::ListenForChanges_Impl_Implementation(const UObject* ContextObject)
{
	if (!ensureAlways(ValueSourceLeft != nullptr && ValueSourceRight != nullptr))
	{
		return;
	}

	ValueSourceLeft->ListenForChanges(ContextObject);
	ValueSourceLeft->OnValueChangedDelegate.AddUniqueDynamic(this, &UMGameplayCondition_CompareFloats::OnFloatValueChanged);

	ValueSourceRight->ListenForChanges(ContextObject);
	ValueSourceRight->OnValueChangedDelegate.AddUniqueDynamic(this, &UMGameplayCondition_CompareFloats::OnFloatValueChanged);
}

void UMGameplayCondition_CompareFloats::StopListeningForChanges_Impl_Implementation(const UObject* ContextObject)
{
	if (!ensureAlways(ValueSourceLeft != nullptr && ValueSourceRight != nullptr))
	{
		return;
	}

	ValueSourceLeft->StopListeningForChanges(ContextObject);
	ValueSourceLeft->OnValueChangedDelegate.RemoveDynamic(this, &UMGameplayCondition_CompareFloats::OnFloatValueChanged);

	ValueSourceRight->StopListeningForChanges(ContextObject);
	ValueSourceRight->OnValueChangedDelegate.RemoveDynamic(this, &UMGameplayCondition_CompareFloats::OnFloatValueChanged);
}

// TODO: finish this
FString UMGameplayCondition_CompareFloats::GetConditionDescriptionString_Implementation() const
{
	if (!ensureAlways(ValueSourceLeft != nullptr && ValueSourceRight != nullptr))
	{
		return TEXT("");
	}

	return Super::GetConditionDescriptionString_Implementation();
}

bool UMGameplayCondition_CompareFloats::CompareFloats(const float ValueLeft, const float ValueRight) const
{
	switch (CompareOp)
	{
	case EMCompareOp::Less:
		return ValueLeft < ValueRight;
	case EMCompareOp::LessOrEqual:
		return ValueLeft <= ValueRight;
	case EMCompareOp::Equal:
		return ValueLeft == ValueRight;
	case EMCompareOp::NotEqual:
		return ValueLeft != ValueRight;
	case EMCompareOp::GreaterOrEqual:
		return ValueLeft >= ValueRight;
	case EMCompareOp::Greater:
		return ValueLeft > ValueRight;
	}

	ensureAlways(false);
	return false;
}

void UMGameplayCondition_CompareFloats::OnFloatValueChanged()
{
	BroadcastOnConditionSourceChanged();
}
