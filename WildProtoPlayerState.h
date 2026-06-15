// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheWildCard_V1/TheWildCard_V1.h"
#include "GameFramework/PlayerState.h"
#include "WildProtoBattleData.h"
#include "WildProtoPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandCountChangedDelegate, int32, NewHandCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyHandUpdatedDelegate, const TArray<FWildCardDisplayData>&, HandData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeckCountChangedDelegate, int32, NewDeckCount);

UCLASS()
class THEWILDCARD_V1_API AWildProtoPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWildProtoPlayerState();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMyHandUpdatedDelegate OnMyHandUpdatedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHandCountChangedDelegate OnHandCountChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeckCountChangedDelegate OnDeckCountChangedDelegate;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int32 GetPlayerID() const { return PlayerID; };

	virtual void BeginPlay() override;

	int32 GetPlayerCount() const { return PlayerCount; };

	UFUNCTION(BlueprintCallable)
	void SetPlayerCount(int32 InPlayerCount) { PlayerCount = InPlayerCount; };

	UFUNCTION(BlueprintCallable, Category = "Stats")
	class UWildProtoStatComponent* GetStatComponent() const { return StatComponent; }
	
private:
	int32 PlayerID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWildProtoStatComponent> StatComponent;
	
	// Battle Sectoin
public:
	UPROPERTY(Replicated)
	bool bIsGamesetReady = false;

	UPROPERTY(Replicated)
	bool bIsMulliganReady = false;

	UPROPERTY(Replicated)
	bool bIsActionReady = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Cards|Server")
	TArray<class UWildProtoCardInstance*> ServerDeck;

	UPROPERTY(VisibleAnywhere, Category = "Cards|Server")
	TArray<class UWildProtoCardInstance*> ServerHand;

	UPROPERTY(VisibleAnywhere, Category = "Cards|Server")
	TArray<class UWildProtoCardInstance*> ServerObliterate;

	UPROPERTY(VisibleAnywhere, Category = "Cards|Server")
	TArray<class UWildProtoCardInstance*> ServerExile;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHandDisplay, BlueprintReadOnly, Category = "Cards|Client")
	TArray<FWildCardDisplayData> CurrentHandDisplay;

	UPROPERTY(ReplicatedUsing = OnRep_ObliterateDisplay, BlueprintReadOnly, Category = "Cards|Client")
	TArray<FWildCardDisplayData> ObliterateDisplay;

	UPROPERTY(ReplicatedUsing = OnRep_HandCount, BlueprintReadOnly, Category = "Cards|Count")
	int32 HandCount;

	UPROPERTY(ReplicatedUsing = OnRep_DeckCount, BlueprintReadOnly, Category = "Cards|Count")
	int32 DeckCount;
	
	
	void DrawCard(FName CardIDToDraw, int32 BaseMana);

	void Debug_GiveDummyStartingHand();

	void CreateTestDeck();

	// 덱 셔플 함수
	void ShuffleDeck();

	UFUNCTION(BlueprintCallable, Category = "Cards|Server")
	class UWildProtoCardInstance* GenerateCardInstance(FName CardRowName);

	UFUNCTION(BlueprintPure, Category = "Cards|Server")
	class UWildProtoCardInstance* FindCardInstanceByID(int32 InInstanceID) const;
	
public:
	void SetPendingMainAction(const FWildActionData& InActionData);
	const FWildActionData& GetPendingMainAction() const;
	void ClearPendingMainAction();
	void SyncHandDataToDisplay();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Action|ServerOnly")
	FWildActionData PendingMainAction;

	UPROPERTY(EditAnywhere, Category = "Cards")
	TObjectPtr<UDataTable> CardDataTable;

	

protected:
	UFUNCTION()
	void OnRep_CurrentHandDisplay();
	UFUNCTION()
	void OnRep_ObliterateDisplay();
	UFUNCTION()
	void OnRep_HandCount();
	UFUNCTION()
	void OnRep_DeckCount();
	UFUNCTION()
	void OnRep_PlayerCount();

public:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerCount)
	int32 PlayerCount;

	// Mulligan

public:
	const TArray<int32>& GetCachedMulliganCards() const { return CachedMulliganCards; }

	void ClearCachedMulliganCards() { CachedMulliganCards.Empty(); }
	
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void Server_SubmitMulligan(const TArray<int32>& CardsToSwap);

	UFUNCTION(Client, Reliable)
	void Client_ReceiveStartingHand(const TArray<FWildCardDisplayData>& FinalHand);

	void ExecuteMulliganSwap();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Cards|ServerOnly")
	TArray<int32> CachedMulliganCards;

	// Artifact
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifact|Server")
	TObjectPtr<class UWildProtoArtifactBase> EquippedArtifact;

	UPROPERTY(ReplicatedUsing = OnRep_ArtifactDisplay, BlueprintReadOnly, Category = "Artifact|Client")
	FWildArtifactDisplayData ArtifactDisplay;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Artifact")
	void Server_SubmitArtifact(FName ArtifactRowName);

	void SyncArtifactToDisplay();
	
	UFUNCTION()
	void OnRep_ArtifactDisplay();
};
