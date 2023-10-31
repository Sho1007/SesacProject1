// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"

#include "../Widget/InGameWidget.h"
#include "GameFramework/Character.h"
#include "../Inventory/InventoryComponent.h"

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

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void AInGamePlayerController::ShowBoxWidget(int32 ItemCount)
{
	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetCharacter()->GetComponentByClass(UInventoryComponent::StaticClass())))
	{
		TArray<FName> ItemNameArray;
		InventoryComponent->GetEnforcableItemName(ItemNameArray, ItemCount);
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
		InGameWidget->ShowBoxWidget(ItemNameArray);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AInGamePlayerController::ShowBoxWidget) Character has no Inventory Component"));
	}
}