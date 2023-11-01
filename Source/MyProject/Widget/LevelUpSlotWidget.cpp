// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/LevelUpSlotWidget.h"

#include <Components/Button.h>
#include <Components/HorizontalBox.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "MyProject/ZombieSurvivalGameInstance.h"
#include "MyProject/Character/StatusComponent.h"
#include "MyProject/Inventory/InventoryComponent.h"
#include "../Weapon/WeaponBase.h"
#include "MyProject/PlayerController/InGamePlayerController.h"

void ULevelUpSlotWidget::Init(FName NewItemName)
{
	if (UZombieSurvivalGameInstance* GameInstance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass())))
		{
			ItemName = NewItemName;

			if (FWeaponData* WeaponData = GameInstance->GetWeaponData(ItemName))
			{
				Img_ItemImage->SetBrushFromTexture(WeaponData->WeaponImage);
				Txt_ItemName->SetText(WeaponData->WeaponName);

				int32 ItemLevel = InventoryComponent->GetItemLevel(ItemName);
				if (ItemLevel > 0)
				{
					HB_ItemLevel->SetVisibility(ESlateVisibility::Visible);
					Txt_ItemLevel->SetText(FText::FromString(FString::FromInt(ItemLevel + 1)));
					Txt_NewWeapon->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
				{
					HB_ItemLevel->SetVisibility(ESlateVisibility::Collapsed);
					Txt_NewWeapon->SetVisibility(ESlateVisibility::Visible);
				}

				Txt_ItemDiscription->SetText(WeaponData->DiscriptionTextArray[ItemLevel]);
			}
			else if (true)
			{
				// Todo : Equipment Data
			}

			SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ULevelUpSlotWidget::Init) Player has no Inventory Component"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ULevelUpSlotWidget::Init) GameInstance is invalid"));
	}
}

bool ULevelUpSlotWidget::Initialize()
{
	bool Result = Super::Initialize();

	Btn_SelectItem->OnClicked.AddDynamic(this, &ULevelUpSlotWidget::OnSelectItemButtonClicked);

	return Result;
}

void ULevelUpSlotWidget::OnSelectItemButtonClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("ULevelUpSlotWidget::OnSelectItemButtonClicked) ItemName : %s"), *ItemName.ToString());

	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass())))
	{
		if (InventoryComponent->AddWeapon(ItemName))
		{
			if (AInGamePlayerController* PC = GetOwningPlayer<AInGamePlayerController>())
			{
				PC->HideLevelUpWidget();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("ULevelUpSlotWidget::OnSelectItemButtonClicked) Player Controller is invalid"));
			}
		}
		else
		{
			// Todo : Equipment
		}
	}
}