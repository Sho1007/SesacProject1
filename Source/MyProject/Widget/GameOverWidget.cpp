// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/GameOverWidget.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(GameOverSound);
	PlaySound(GameOverSound);
}