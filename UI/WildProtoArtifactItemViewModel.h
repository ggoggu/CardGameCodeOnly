// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Artifact/WildArtifactData.h"
#include "WildProtoArtifactItemViewModel.generated.h"

/**
 * 
 */
UCLASS()
class THEWILDCARD_V1_API UWildProtoArtifactItemViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void InitializeFromData(const FArtifactData& InData);

	UFUNCTION(BlueprintCallable, Category = "Artifact")
	void ToggleSelection();

	FName GetArtifactID() const { return ArtifactID; }

public:
	// MVVM 바인딩을 위한 변수 선언
	UPROPERTY(BlueprintReadWrite, FieldNotify, Category = "Artifact")
	FName ArtifactID;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Category = "Artifact")
	FText ArtifactName;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Category = "Artifact")
	FText EffectText;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Category = "Artifact")
	TSoftObjectPtr<UTexture2D> ArtifactImage;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Category = "Artifact")
	bool bIsSelected;

public:
	// MVVM Getter/Setter 매크로 구현부
	void SetArtifactID(FName InID) { UE_MVVM_SET_PROPERTY_VALUE(ArtifactID, InID); }
	void SetArtifactName(FText InName) { UE_MVVM_SET_PROPERTY_VALUE(ArtifactName, InName); }
	void SetEffectText(FText InText) { UE_MVVM_SET_PROPERTY_VALUE(EffectText, InText); }
	void SetArtifactImage(TSoftObjectPtr<UTexture2D> InImage) { UE_MVVM_SET_PROPERTY_VALUE(ArtifactImage, InImage); }
	
	void SetbIsSelected(bool bInSelected) { UE_MVVM_SET_PROPERTY_VALUE(bIsSelected, bInSelected); }
	bool GetbIsSelected() const { return bIsSelected; }
	
};
