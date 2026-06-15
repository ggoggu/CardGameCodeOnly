// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheWildCard_V1/TheWildCard_V1.h"
#include "GameFramework/GameState.h"
#include "WildProtoBattleData.h"
#include "WildProtoGameState.generated.h"

/**
 * 
 */
enum class EWildCardPhase : uint8;
class AWildMapMaker;
class AWildProtoUnitBase;
class UWildProtoChainComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChangedDelegate, int32, RemainTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChangeDelegate, EWildCardPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangeDelegate, EWildMatchState, NewMatchState);

UCLASS()
class THEWILDCARD_V1_API AWildProtoGameState : public AGameState
{
	GENERATED_BODY()

public:
	AWildProtoGameState();
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Event Bus
	UPROPERTY(BlueprintAssignable, Category = "Event Bus")
	FOnTurnStartedDelegate OnTurnStartedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Event Bus")
	FOnTurnEndedDelegate OnTurnEndedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Event Bus")
	FOnPhaseChangeDelegate OnPhaseChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Event Bus")
	FOnTimerChangedDelegate OnTimerChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Event Bus")
	FOnMatchStateChangeDelegate OnMatchStateChangedDelegate;
	
	/* 아직 사용 x */
	UPROPERTY(VisibleAnywhere, Category = "Board")
	TArray<AWildProtoUnitBase*> ActiveUnitsOnBoard;
	
	void RegisterUnit(AWildProtoUnitBase* NewUnit);
	void UnregisterUnit(AWildProtoUnitBase* DeadUnit);
	/*			*/

	EWildCardPhase GetCurrentPhase() const { return CurrentPhase; };
	void SetCurrentPhase(EWildCardPhase NewPhase);

	int32 GetPhaseRemainTime() const { return PhaseRemainTime; }
	void SetPhaseRemainTime(int32 NewTime);

	int32 GetCurrentPriorityPlayerID() const { return CurrentPriorityPlayerID; }
	void SetCurrentPriorityPlayerID(int32 NewPlayerID);

	int GetCurrentChainPromptID() const { return CurrentChainPromptID; }
	void SetCurrentChainPromptID(int32 InPlayerID);

	EWildMatchState GetCurrentMatchState() const { return CurrentMatchState; }
	void SetCurrentMatchState(EWildMatchState NewState);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentMatchState, BlueprintReadOnly, Category = "Match")
	EWildMatchState CurrentMatchState;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentPhase, BlueprintReadOnly, Category = "Phase")
	EWildCardPhase CurrentPhase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWildProtoChainComponent> ChainComponent;

	UPROPERTY(ReplicatedUsing = OnRep_PriorityPlayerChanged, BlueprintReadOnly, Category = "Phase")
	int32 CurrentPriorityPlayerID;

	UPROPERTY(ReplicatedUsing = OnRep_PhaseRemainTime, BlueprintReadOnly, Category = "Phase")
	int32 PhaseRemainTime;
	
	UPROPERTY(ReplicatedUsing = OnRep_ChainPromptPlayerChanged, BlueprintReadOnly, Category = "WildCard|State")
	int32 CurrentChainPromptID;
	

	UFUNCTION() void OnRep_CurrentMatchState();
	UFUNCTION() void OnRep_CurrentPhase();
	UFUNCTION() void OnRep_PriorityPlayerChanged();
	UFUNCTION() void OnRep_PhaseRemainTime();
	UFUNCTION() void OnRep_ChainPromptPlayerChanged();

	

};