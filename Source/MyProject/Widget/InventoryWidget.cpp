// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryWidget.h"

#include "../Inventory/InventoryComponent.h"
#include "Components/Image.h"
#include "MyProject/Weapon/WeaponBase.h"
#include "../ZombieSurvivalGameInstance.h"
#include "MyProject/Weapon/EquipmentBase.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass()));

	check(InventoryComponent);

	InventoryComponent->OnInventoryUpdated.BindUObject(this, &UInventoryWidget::UpdateInventory);

	WeaponImageArray.Add(Img_Weapon1);
	WeaponImageArray.Add(Img_Weapon2);
	WeaponImageArray.Add(Img_Weapon3);
	WeaponImageArray.Add(Img_Weapon4);
	WeaponImageArray.Add(Img_Weapon5);
	WeaponImageArray.Add(Img_Weapon6);

	EquipmentImageArray.Add(Img_Equipment1);
	EquipmentImageArray.Add(Img_Equipment2);
	EquipmentImageArray.Add(Img_Equipment3);
	EquipmentImageArray.Add(Img_Equipment4);
	EquipmentImageArray.Add(Img_Equipment5);
	EquipmentImageArray.Add(Img_Equipment6);
}

void UInventoryWidget::UpdateInventory()
{
	UZombieSurvivalGameInstance* GameInstance = GetGameInstance<UZombieSurvivalGameInstance>();
	check(GameInstance);

	const TArray<AWeaponBase*>& WeaponArray = InventoryComponent->GetWeaponArray();
	const TArray<AEquipmentBase*>& EquipmentArray = InventoryComponent->GetEquipmentArray();

	for (int i = 0; i < 6; ++i)
	{
		if (i < WeaponArray.Num())
		{
			// Has Weapon At i

			FWeaponData* WeaponData = GameInstance->GetWeaponData(WeaponArray[i]->GetWeaponName());

			WeaponImageArray[i]->SetVisibility(ESlateVisibility::HitTestInvisible);
			WeaponImageArray[i]->SetBrushFromTexture(WeaponData->WeaponImage);
		}
		else
		{
			// No Weapon At i
			WeaponImageArray[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		if (i < EquipmentArray.Num())
		{
			// Has Equipment At i

			FEquipmentData* EquipmentData = GameInstance->GetEquipmentData(EquipmentArray[i]->GetEquipmentName());

			EquipmentImageArray[i]->SetVisibility(ESlateVisibility::HitTestInvisible);
			EquipmentImageArray[i]->SetBrushFromTexture(EquipmentData->EquipmentImage);
		}
		else
		{
			// No Equipment At i
			EquipmentImageArray[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}