// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateWidget.generated.h"

/**
 * 
 */
class AZombieSurvivalGameState;
class UTextBlock;
UCLASS()
class MYPROJECT_API UGameStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UpdateGameTime(float NewGameTime);

	void UpdateCoin(int32 NewCoin);
	void UpdateMonsterCount(int32 NewMonsterCount);

private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_Minute;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_Second;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_Monster;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_Coin;

	AZombieSurvivalGameState* GameState;
};
