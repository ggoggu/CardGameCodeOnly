// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WildProtoBattleData.h"
#include "WildProtoChainComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChainUpdated, int32, CurrentStackCount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEWILDCARD_V1_API UWildProtoChainComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWildProtoChainComponent();
	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintAssignable) FOnChainUpdated OnChainUpdatedDelegate;
	
	void AddActionToChain(const FWildActionData& NewAction);
	void ResolveChain();
	void DeclareAction(const FWildActionData& ActionData);
	void ProcessNextMainAction();

protected:
	UPROPERTY()
	TArray<FWildActionData> MainActionQueue;

	UPROPERTY()
	TArray<FWildActionData> PendingResolutionMainActions;
	
	UPROPERTY(ReplicatedUsing = OnRep_ActionStack)
	TArray<FWildActionData> ActionStack;
	
	UPROPERTY(Replicated)
	int32 ActionCount;

	void ProcessMiddlePhase();

	void ExecuteMainActionsSimultaneously();
	
	UFUNCTION()
	void OnRep_ActionStack();

	UFUNCTION()
	void OnServerPhaseChanged(EWildCardPhase NewPhase);

private:
	
	void ExecuteAction(const FWildActionData& ActionData);
	

		
};
