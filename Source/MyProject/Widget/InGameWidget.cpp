// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InGameWidget.h"

#include "BoxWidget.h"
#include "LevelUpWidget.h"
#include "Animation/UMGSequencePlayer.h"

void UInGameWidget::ShowBoxWidget(const TArray<FName>& ItemNameArray)
{
	BoxWidget->ShowWidget(ItemNameArray);
}

void UInGameWidget::ShowLevelUpWidget(const TArray<FName>& ItemNameArray)
{
	PlayAnimation(LevelUpAnimation);
	LevelUpWidget->ShowWidget(ItemNameArray);
}

void UInGameWidget::HideLevelUpWidget()
{
	LevelUpWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UInGameWidget::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	if (Player.GetAnimation() == LevelUpAnimation)
	{

	}
}
