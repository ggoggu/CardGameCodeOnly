// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheWildCard_V1/TheWildCard_V1.h"
#include "Engine/GameInstance.h"
#include "WildProtoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEWILDCARD_V1_API UWildProtoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<class UDataTable> CardDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<class UDataTable> ArtifactDataTable;
	
};
