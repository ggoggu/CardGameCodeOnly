// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WildProtoPawn.generated.h"

class UWildCameraComponent;
class AWildCardActor;
class AWildTile;
struct FCardData;

UCLASS()
class THEWILDCARD_V1_API AWildProtoPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWildProtoPawn();

	UFUNCTION(Server, Reliable)
	void Server_SpawnUnitActor(FCardData InCardData, AWildTile* InTile, TSubclassOf<AWildCardActor> InUnitClass);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerYawInput(float Val) override;

private:
	void ToggleYawLock();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWildCameraComponent> CameraComponent;

	bool bIsYawLocked;

};
