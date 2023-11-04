// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSurvivalGameState.h"

AZombieSurvivalGameState::AZombieSurvivalGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieSurvivalGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GameTime += DeltaSeconds;

	UE_LOG(LogTemp, Warning, TEXT("AZombieSurvivalGameState::Tick"));

	OnGameTimeUpdated.ExecuteIfBound(GameTime);
}

void AZombieSurvivalGameState::AddMonsterCount()
{
	MonsterCount++;

	OnMonsterCountUpdated.ExecuteIfBound(MonsterCount);
}

void AZombieSurvivalGameState::AddCoin(int32 NewCoin)
{
	Coin += NewCoin;

	OnCoinUpdated.ExecuteIfBound(Coin);
}