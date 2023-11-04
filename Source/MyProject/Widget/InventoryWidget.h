// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UImage;
class UInventoryComponent;
UCLASS()
class MYPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateInventory();

private:
	UInventoryComponent* InventoryComponent;

	TArray<UImage*> WeaponImageArray;
	TArray<UImage*> EquipmentImageArray;

	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon1;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon2;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon3;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon4;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon5;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Weapon6;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment1;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment2;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment3;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment4;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment5;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Equipment6;
};
