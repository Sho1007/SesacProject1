// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/ExpBarWidget.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

#include "../Character/PlayerBase.h"

void UExpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerBase* Player = Cast<APlayerBase>(GetOwningPlayerPawn());
	check(Player);

	Player->OnExpUpdated.BindUObject(this, &UExpBarWidget::UpdateExp);
	Player->OnLevelUpdated.BindUObject(this, &UExpBarWidget::UpdateLevel);
}

void UExpBarWidget::UpdateExp(float CurrentExp, float MaxExp)
{
	PrgBar_ExpBar->SetPercent(CurrentExp / MaxExp);
}

void UExpBarWidget::UpdateLevel(int32 CurrentLevel)
{
	Txt_Level->SetText(FText::FromString(FString::FromInt(CurrentLevel)));
}