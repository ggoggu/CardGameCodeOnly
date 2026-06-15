// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WildProtoBattleData.h"
#include "Interface/WildHUDHandle.h"
#include "WildProtoControllerPhase.generated.h"

class UWildHUDWidget;
/**
 * 
 */
UCLASS()
class THEWILDCARD_V1_API AWildProtoControllerPhase : public APlayerController,public IWildHUDHandle
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CompleteMulligan();

	UFUNCTION(BlueprintCallable)
	void PlayChainCard(const FWildActionData& ActionData);

	UFUNCTION(BlueprintCallable)
	void PassChain();

	UFUNCTION(BlueprintCallable)
	void CompleteGameset();

	UFUNCTION(BlueprintCallable)
	void CompletePrivateAction(const FWildActionData& ActionData);

	void RefreshMulliganUI(const TArray<FWildCardDisplayData>& NewCards);

protected:

	FTimerHandle BindTimer;
	
	virtual void BeginPlay() override;

	// 다양한 케이스 테스트용으로 불피요시 지울 수 ㅣㅇㅆ음
	void TryBindGameState();
	
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_CompleteMulligan();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlayChainCard(const FWildActionData& ActionData);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PassChain();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_CompleteGameset();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_CompletePrivateAction(const FWildActionData& ActionData);

	UFUNCTION()
	void OnMatchStateChanged(EWildMatchState NewState);
	
	UFUNCTION()
	void OnGamePhaseChanged(EWildCardPhase NewPhase);
	
	// Debug
public:
	UFUNCTION(BlueprintCallable, Category = "Debug|Phase")
	void Debug_Ready();
	
	UFUNCTION(BlueprintCallable, Category = "Debug|Phase")
	void Debug_Pass();

	UFUNCTION(BlueprintCallable, Category = "Debug|Phase")
	void Debug_Chain();

	// Widget
public:
	virtual FSliderChanged& GetOnCardOpacityChanged() override { return OnCardOpacityChanged; }
	virtual FSliderChanged& GetOnCardYaxisChanged() override { return OnCardYaxisChanged; };
	
	FSliderChanged OnCardYaxisChanged;
	FSliderChanged OnCardOpacityChanged;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> MulliganWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWildHUDWidget> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> GamesetWidgetClass;

private:
	UPROPERTY()
	class UUserWidget* MulliganWidgetInstance;
	
	UPROPERTY()
	UWildHUDWidget* HUDInstance;

	UPROPERTY()
	class UUserWidget* GamesetWidgetInstance;
	
	void ShowMulliganUI();
	void HideMulliganUI();
	void CreateHUD();
	void ConnectInHUD();
	void ConnectDelegate();
	
	void ShowGamesetUI();
	void HideGamesetUI();

	UFUNCTION()
	void OnTimerUpdated(int32 RemainTime);
};
