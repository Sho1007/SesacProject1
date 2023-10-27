// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BoxWidget.h"

void UBoxWidget::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::ShowWidget) Player Character Name : %s"), *GetOwningPlayerPawn()->GetName());
	GetOwningPlayer()->SetPause(true);
}