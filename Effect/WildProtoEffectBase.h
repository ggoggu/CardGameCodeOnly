// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WildProtoBattleData.h"
#include "WildProtoEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class THEWILDCARD_V1_API UWildProtoEffectBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Setting")
	EWildEffectTriggerTiming TriggerTiming = EWildEffectTriggerTiming::Instant;

	UFUNCTION(BlueprintNativeEvent, Category = "Card Effect")
	void ExecuteEffect(const FWildActionData& ActionData);
	virtual void ExecuteEffect_Implementation(const FWildActionData& ActionData) PURE_VIRTUAL(UWildCardEffectBase::ExecuteEffect_Implementation, );

	virtual UWorld* GetWorld() const override;
	
};
