// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include  "WildProtoEffectBase.h"
#include "WildProtoCardDataAsset.generated.h"

/**
 * 
 */
 
 // Only For Test
UCLASS()
class THEWILDCARD_V1_API UWildProtoCardDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Info")
    	FName CardName;
    
    	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Info")
    	int32 ManaCost;
    
    	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Card Effects")
    	TArray<UWildProtoEffectBase*> CardEffects;
};
