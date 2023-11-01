// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */
class UVerticalBox;
class UTextBlock;
UCLASS()
class MYPROJECT_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowWidget(const TArray<FName>& ItemNameArray);
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UVerticalBox* VB_ItemSlot;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_LuckInformation;
};