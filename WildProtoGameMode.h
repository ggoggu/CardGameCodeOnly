// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WildProtoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THEWILDCARD_V1_API AWildProtoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AWildProtoGameMode();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerCount() const { return Server_PlayerCount; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerCount(int32 NewPlayerCount) { Server_PlayerCount = NewPlayerCount; }

	//TODO : Hand Draw �� Unit ���� ���� �����ö� �׽�Ʈ
	int32 GenerateNextCardInstanceID();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

public:
	int32 Server_PlayerCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UWildProtoPhaseComponent> PhaseComponent;

private:
	int32 CurrentCardInstanceID = 123;

};
