// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/LevelUpWidget.h"

#include <Components/VerticalBox.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#include "LevelUpSlotWidget.h"

//#include "Item"

void ULevelUpWidget::ShowWidget(const TArray<FName>& ItemNameArray)
{
	//UE_LOG(LogTemp, Warning, TEXT("ULevelUpWidget::ShowWidget"));

	// Turn off all children

	check(LevelUpSound);
	UGameplayStatics::PlaySound2D(GetWorld(), LevelUpSound);


	for (int i = 0; i < VB_ItemSlot->GetChildrenCount(); ++i)
	{
		VB_ItemSlot->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (ItemNameArray.Num() == 4)
	{
		Txt_LuckInformation->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Txt_LuckInformation->SetVisibility(ESlateVisibility::Visible);
	}
	
	for (int i = 0; i < ItemNameArray.Num(); ++i)
	{
		if (ULevelUpSlotWidget* LevelUpSlotWidget = Cast<ULevelUpSlotWidget>(VB_ItemSlot->GetChildAt(i)))
		{
			LevelUpSlotWidget->Init(ItemNameArray[i]);
		}
	}

	SetVisibility(ESlateVisibility::Visible);
}