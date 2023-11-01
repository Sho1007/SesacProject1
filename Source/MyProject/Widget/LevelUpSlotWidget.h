// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpSlotWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UHorizontalBox;
class UButton;
UCLASS()
class MYPROJECT_API ULevelUpSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FName NewItemName);

	virtual bool Initialize() override;

	UFUNCTION()
	void OnSelectItemButtonClicked();
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess))
	FName ItemName;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UButton* Btn_SelectItem;
	
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_ItemImage;

	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UHorizontalBox* HB_ItemLevel;

	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_ItemName;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_ItemLevel;

	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_NewWeapon;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_ItemDiscription;
};