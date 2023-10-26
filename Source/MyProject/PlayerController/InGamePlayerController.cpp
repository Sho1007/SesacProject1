// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"

#include "../Widget/InGameWidget.h"

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (InGameWidgetClass)
	{
		InGameWidget = CreateWidget<UInGameWidget>(this, InGameWidgetClass, TEXT("InGameWidget"));
		check(InGameWidget);
		InGameWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AInGamePlayerController::BeginPlay) InGameWidgetClass is nullptr"));
	}
}

void AInGamePlayerController::ShowBoxWidget(int32 ItemCount)
{

	InGameWidget->ShowBoxWidget();
}