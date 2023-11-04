// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/GameStateWidget.h"

#include <Components/TextBlock.h>

#include "../ZombieSurvivalGameState.h"

void UGameStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameState = GetWorld()->GetGameState<AZombieSurvivalGameState>();
	check(GameState);

	GameState->OnCoinUpdated.BindUObject(this, &UGameStateWidget::UpdateCoin);
	GameState->OnMonsterCountUpdated.BindUObject(this, &UGameStateWidget::UpdateMonsterCount);

	GameState->OnGameTimeUpdated.BindUObject(this, &UGameStateWidget::UpdateGameTime);
}

void UGameStateWidget::UpdateGameTime(float NewGameTime)
{
	int32 GameTime = (int32)NewGameTime;
	Txt_Minute->SetText(FText::FromString(FString::FromInt(GameTime / 60)));
	Txt_Second->SetText(FText::FromString(FString::FromInt(GameTime % 60)));
}

void UGameStateWidget::UpdateCoin(int32 NewCoin)
{
	Txt_Coin->SetText(FText::FromString(FString::FromInt(NewCoin)));
}

void UGameStateWidget::UpdateMonsterCount(int32 NewMonsterCount)
{
	Txt_Monster->SetText(FText::FromString(FString::FromInt(NewMonsterCount)));
}