	// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/LevelUpSlotWidget.h"

#include <Components/Button.h>
#include <Components/HorizontalBox.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "MyProject/ZombieSurvivalGameInstance.h"
#include "MyProject/Inventory/InventoryComponent.h"
#include "../Weapon/WeaponBase.h"
#include "../Weapon/EquipmentBase.h"
#include "MyProject/ObjectPooling/ItemBase.h"
#include "MyProject/PlayerController/InGamePlayerController.h"

void ULevelUpSlotWidget::Init(FName NewItemName)
{
	UZombieSurvivalGameInstance* GameInstance = GetGameInstance<UZombieSurvivalGameInstance>();
	check(GameInstance);
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass()));
	check(InventoryComponent);

	ItemName = NewItemName;

	SetVisibility(ESlateVisibility::Visible);

	int32 ItemLevel = InventoryComponent->GetItemLevel(ItemName);
	if (FWeaponData* WeaponData = GameInstance->GetWeaponData(ItemName))
	{
		Img_ItemImage->SetBrushFromTexture(WeaponData->WeaponImage);
		//Img_ItemImage->SetDesiredSizeOverride(FVector2D(100, 100));
		Txt_ItemName->SetText(WeaponData->WeaponName);
		Txt_ItemDiscription->SetText(WeaponData->DiscriptionTextArray[ItemLevel]);
	}
	else if (FEquipmentData* EquipmentData = GameInstance->GetEquipmentData(ItemName))
	{
		Img_ItemImage->SetBrushFromTexture(EquipmentData->EqiupmentImage);
		//Img_ItemImage->SetDesiredSizeOverride(FVector2D(100, 100));
		Txt_ItemName->SetText(EquipmentData->EquipmentName);
		Txt_ItemDiscription->SetText(EquipmentData->DiscriptionTextArray[ItemLevel]);
	}
	else if (FItemData* ItemData = GameInstance->GetItemData(ItemName))
	{
		Img_ItemImage->SetBrushFromTexture(ItemData->ItemImage);
		//Img_ItemImage->SetDesiredSizeOverride(FVector2D(100, 100));
		Txt_ItemName->SetText(ItemData->ItemName);
		Txt_ItemDiscription->SetText(ItemData->DiscriptionTextArray[ItemLevel]);

		HB_ItemLevel->SetVisibility(ESlateVisibility::Collapsed);
		Txt_NewWeapon->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

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

	AInGamePlayerController* PC = GetOwningPlayer<AInGamePlayerController>();
	check(PC);

	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass())))
	{
		if (InventoryComponent->AddWeapon(ItemName))
		{
			PC->HideLevelUpWidget();
		}
		else if (InventoryComponent->AddEquipment(ItemName))
		{
			PC->HideLevelUpWidget();
		}
		else if (InventoryComponent->AddItem(ItemName))
		{
			PC->HideLevelUpWidget();
		}
	}
}