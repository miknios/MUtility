// Copyright (c) Miknios. All rights reserved.


#include "MClass.h"

FString M::Class::GetClassDisplayName(const UClass& Class)
{
#if WITH_EDITORONLY_DATA
	return Class.GetDisplayNameText().ToString();
#else
	return Class.GetName();
#endif
}

FString UMClassLibrary::GetClassDisplayName(const UClass* Class)
{
	if (Class == nullptr)
	{
		return TEXT("Invalid Class");
	}
	
	return M::Class::GetClassDisplayName(*Class);
}
