// Copyright (c) Miknios. All rights reserved.


#include "MMeshStatics.h"

void UMMeshStatics::AttachComponentsSocketAligned(USceneComponent* ChildComponent, const FName ChildSocket,
                                                  USceneComponent* ParentComponent, const FName ParentSocket)
{
	ChildComponent->AttachToComponent(
		ParentComponent,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		ParentSocket);

	const FTransform ChildSocketLocalTransform = ChildComponent->GetSocketTransform(ChildSocket, RTS_Component);
	const FTransform InverseChildSocketLocalTransform = ChildSocketLocalTransform.Inverse();
	ChildComponent->SetRelativeTransform(InverseChildSocketLocalTransform);
}
