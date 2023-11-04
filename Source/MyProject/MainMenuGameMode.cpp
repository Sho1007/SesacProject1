// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "Widget/MainMenuWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Create Main Menu Widget
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(PC);
	check(MainMenuWidgetClass);
	MainMenuWidget = CreateWidget<UMainMenuWidget>(PC, MainMenuWidgetClass);
	check(MainMenuWidget);
	MainMenuWidget->AddToViewport();
}