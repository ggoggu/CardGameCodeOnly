// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WildProtoBattleData.generated.h"

/**
 * 
 */

class AWildProtoUnitBase;

UENUM(BlueprintType)
enum class EWildMatchState : uint8
{
	Init,               // 게임 시작 전 (플레이어 접속 대기)
	Gameset,            // 성유물, 전술 스킬 비공개 선택
	Mulligan,           // 5장 드로우 및 교체할 카드 선택
	Mulligan_End,       // [신규] 교체 애니메이션 대기 및 서버에서 새 카드 꽂아주는 시간
	MainGame,           // [신규] 본 게임 진행 중 (이 상태일 때만 아래의 TurnPhase가 돕니다)
	Match_End           // 승패 결정 및 결과 화면
};

UENUM(BlueprintType)
enum class EWildCardPhase : uint8
{
	None UMETA(DisplayName = "페이즈 없음"),               
	Turn_Start UMETA(DisplayName = "턴 시작"),             
	Action_Private UMETA(DisplayName = "비공개 행동 결정"),
	Action_Public UMETA(DisplayName = "체인 대기 (공개)"), 
	Action_Resolution UMETA(DisplayName = "체인 처리"),   
	Turn_End UMETA(DisplayName = "턴 종료")
};

UENUM(BlueprintType)
enum class EWildActionCategory : uint8
{
	None,
	Main,   // 메인 행동 (비공개 제출, 동시 처리)
	Sub     // 서브 행동 (공개 체인 공방용)
};

UENUM(BlueprintType)
enum class EWildActionType : uint8
{
	None,
	
	SummonUnit,     
	CastSpell,

	CastArtifact,    
	CastTacticalSkill,
	
	TriggerTrap,    
	UnitMove,       
	UnitAttack
};

UENUM(BlueprintType)
enum class EWildEffectTriggerTiming : uint8
{
	Instant = 0,     
	TurnStart,       
	TurnEnd,         
	OnTakeDamage,    
	OnDeath          
};

USTRUCT(BlueprintType)
struct THEWILDCARD_V1_API FWildCardDisplayData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 InstanceID; 

	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	FName CardID; 

	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 CurrentManaCost;
	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 Force;
	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 Intelligence;
	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 Attack;
	UPROPERTY(BlueprintReadOnly, Category = "Card Display")
	int32 Health;

	bool operator==(const FWildCardDisplayData& Other) const
	{
		return CardID == Other.CardID;
	}

	FWildCardDisplayData() : InstanceID(-1), CardID(NAME_None), CurrentManaCost(0),Force(0), Intelligence(0), Attack(0), Health(0) {}
	FWildCardDisplayData(int32 InID, FName InCardID, int32 InMana, int32 InForce, int32 InIntelligence, int32 InAttack, int32 InHealth) : InstanceID(InID), CardID(InCardID), CurrentManaCost(InMana),Force(InForce), Intelligence(InIntelligence), Attack(InAttack), Health(InHealth)  {}
};

USTRUCT(BlueprintType)
struct THEWILDCARD_V1_API FWildArtifactDisplayData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Artifact Display")
	FName ArtifactID; 

	UPROPERTY(BlueprintReadOnly, Category = "Artifact Display")
	int32 CurrentDurability;

	UPROPERTY(BlueprintReadOnly, Category = "Artifact Display")
	int32 MaxDurability;

	UPROPERTY(BlueprintReadOnly, Category = "Artifact Display")
	bool bIsActive;

	FWildArtifactDisplayData() : ArtifactID(NAME_None), CurrentDurability(0), MaxDurability(0), bIsActive(false) {}
	FWildArtifactDisplayData(FName InID, int32 InCurrent, int32 InMax, bool InActive) 
		: ArtifactID(InID), CurrentDurability(InCurrent), MaxDurability(InMax), bIsActive(InActive) {}
};

USTRUCT(BlueprintType)
struct THEWILDCARD_V1_API FWildActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Action")
	int32 PlayerID;

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	EWildActionCategory ActionCategory;

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	EWildActionType ActionType;

	UPROPERTY(BlueprintReadWrite, Category = "Action|From Hand")
	int32 CardInstanceID;

	UPROPERTY(BlueprintReadWrite, Category = "Action|On Board")
	TObjectPtr<AWildProtoUnitBase> SourceUnit;

	UPROPERTY(BlueprintReadWrite, Category = "Action|Target")
	int32 TargetPlayerID;

	UPROPERTY(BlueprintReadWrite, Category = "Action|On Board")
	TObjectPtr<AWildProtoUnitBase> TargetUnit;

	UPROPERTY(BlueprintReadWrite, Category = "Action|Target")
	int32 TargetCardInstanceID;

	UPROPERTY(BlueprintReadWrite, Category = "Action|On Board")
	FIntPoint TargetGridPos;

	FWildActionData()
		: PlayerID(-1)
		, ActionCategory(EWildActionCategory::None)
		, ActionType(EWildActionType::None)
		, CardInstanceID(-1)
		, SourceUnit(nullptr)
		, TargetPlayerID(-1)
		, TargetUnit(nullptr)
		, TargetCardInstanceID(-1)
		, TargetGridPos(FIntPoint(-1, -1))
	{}
};