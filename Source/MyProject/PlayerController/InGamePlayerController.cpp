// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"

#include "../Widget/InGameWidget.h"
#include "GameFramework/Character.h"
#include "../Inventory/InventoryComponent.h"
#include "MyProject/Character/StatusComponent.h"

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

void AInGamePlayerController::ShowLevelUpWidget()
{
	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetCharacter()->GetComponentByClass(UInventoryComponent::StaticClass())))
	{
		int32 ItemCount = 3;
		if (UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetCharacter()->GetComponentByClass(UStatusComponent::StaticClass())))
		{
			if (StatusComponent->GetLuck() >= 100.0f)
			{
				ItemCount++;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AInGamePlayerController::ShowLevelUpWidget) Player has no Status Component"));
		}

		TArray<FName> ItemNameArray;
		InventoryComponent->GetAddableItemName(ItemNameArray, ItemCount);
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
		InGameWidget->ShowLevelUpWidget(ItemNameArray);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AInGamePlayerController::ShowBoxWidget) Character has no Inventory Component"));
	}
}

void AInGamePlayerController::HideLevelUpWidget()
{
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
	InGameWidget->HideLevelUpWidget();
}