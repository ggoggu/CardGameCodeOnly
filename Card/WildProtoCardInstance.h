// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WildProtoCardInstance.generated.h"

/**
 * 
 */

class UWildProtoEffectBase;
UCLASS()
class THEWILDCARD_V1_API UWildProtoCardInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 InstanceID;

	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	FName CardID;

	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 CurrentManaCost;

	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 CurrentForce;
	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 CurrentIntelligence;
	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 CurrentAttack;
	UPROPERTY(VisibleAnywhere, Category = "Card Instance")
	int32 CurrentHealth;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "Card Instance")
	TArray<UWildProtoEffectBase*> CardEffects;

	void InitializeCard(int32 InInstanceID, FName InCardID, int32 BaseMana, int32 BaseForce, int32 BaseInt, int32 BaseAtk, int32 BaseHP);
	
};
