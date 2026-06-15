// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WildHUDHandle.generated.h"

// This class does not need to be modified.

DECLARE_MULTICAST_DELEGATE_OneParam(FSliderChanged, float InValue);

UINTERFACE(MinimalAPI)
class UWildHUDHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEWILDCARD_V1_API IWildHUDHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FSliderChanged& GetOnCardOpacityChanged() = 0;
	
	virtual FSliderChanged& GetOnCardYaxisChanged() = 0;
};
