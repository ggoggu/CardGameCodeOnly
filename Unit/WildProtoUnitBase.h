// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WildProtoUnitBase.generated.h"

enum class EWildEffectTriggerTiming : uint8;
class UWildProtoEffectBase;

UCLASS()
class THEWILDCARD_V1_API AWildProtoUnitBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWildProtoUnitBase();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Unit Stats")
	int32 CurrentHealth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Unit Stats")
	int32 CurrentAttack;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "Unit Skills")
	TArray<UWildProtoEffectBase*> ActiveEffects;

	UFUNCTION(BlueprintCallable, Category = "Unit Skills")
	void ProcessEffectsByTiming(EWildEffectTriggerTiming CurrentTiming);

	void InitializeUnitEffects(const TArray<UWildProtoEffectBase*>& InheritedEffects);

	UFUNCTION(BlueprintCallable, Category = "Unit Action")
	virtual void TakeDamage(int32 DamageAmount);

protected:
	UFUNCTION() void HandleTurnEnded();

};
