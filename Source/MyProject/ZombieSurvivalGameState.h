// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ZombieSurvivalGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AZombieSurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AZombieSurvivalGameState();

	virtual void Tick(float DeltaSeconds) override;
	
	void AddMonsterCount();
	void AddCoin(int32 NewCoin);
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess))
	float GameTime;
	UPROPERTY(Meta = (AllowPrivateAccess))
	int32 MonsterCount;
	UPROPERTY(Meta = (AllowPrivateAccess))
	int32 Coin;

public:
	// Delegate
	DECLARE_DELEGATE_OneParam(FDele_Single_One_Float, float);
	FDele_Single_One_Float OnGameTimeUpdated;
	DECLARE_DELEGATE_OneParam(FDele_Single_One_Int32, int32);
	FDele_Single_One_Int32 OnCoinUpdated;
	FDele_Single_One_Int32 OnMonsterCountUpdated;
};