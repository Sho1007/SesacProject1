// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BoxWidget.h"

#include <Components/Image.h>

#include <Animation/UMGSequencePlayer.h>
#include <Animation/WidgetAnimation.h>

#include "../Inventory/InventoryComponent.h"


bool UBoxWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (Item1Animation) Item1Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;
	if (Item3Animation) Item3Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;
	if (Item5Animation) Item5Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;

	return Result;
}

void UBoxWidget::ShowWidget(const TArray<FName>& NewItemNameArray)
{
	ItemNameArray = NewItemNameArray;

	/*
	FString PrintName;
	for (int i = 0; i < ItemNameArray.Num(); ++i)
	{
		PrintName += " " + ItemNameArray[i].ToString();
	}

	UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::ShowWidget) Item : %s"), *PrintName);
	*/

	SetVisibility(ESlateVisibility::Visible);
	//UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::ShowWidget) Player Character Name : %s"), *GetOwningPlayerPawn()->GetName());
	GetOwningPlayer()->SetPause(true);
	PlayAnimation(BoxAnimation);
}

void UBoxWidget::HideWidget()
{
	Img_Item1->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item2->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item3->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item4->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item5->SetVisibility(ESlateVisibility::Collapsed);

	SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->SetPause(false);
}

void UBoxWidget::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	if (Player.GetAnimation() == BoxAnimation)
	{
		switch(ItemNameArray.Num())
		{
		case 1:
			PlayAnimation(Item1Animation);
			break;
		case 3:
			PlayAnimation(Item3Animation);
			break;
		case 5:
			PlayAnimation(Item5Animation);
			break;
		}
	}
	else
	{
		// Show Item;

		CurrentItemIndex = 0;

		GetWorld()->GetTimerManager().SetTimer(SetItemImageTimerHandle, this, &UBoxWidget::SetItemImage, 1.0f, true, 1.0f);

		//HideWidget();
	}

	//UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::OnAnimationFinishedPlaying"));
}

void UBoxWidget::SetItemImage()
{
	if (ItemNameArray.Num() == CurrentItemIndex)
	{
		GetWorld()->GetTimerManager().ClearTimer(SetItemImageTimerHandle);
		HideWidget();
	}
	else
	{
		UTexture2D* ItemImage = nullptr;
		if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayer()->GetComponentByClass(UInventoryComponent::StaticClass())))
		{
			if (InventoryComponent->AddWeapon(ItemNameArray[CurrentItemIndex]))
			{
				// GameInstance 에서 DataTable 찾아서 FItemData 에서 Weapon Image 읽어오기
			}
			else
			{
				// GameInstance 에서 DataTable 찾아서 FItemData 에서 Money Image 읽어오기
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Player has no Inventory Component"));
		}
		switch (CurrentItemIndex)
		{
		case 1:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			break;
		case 2:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			break;
		case 3:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			break;
		case 4:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			break;
		case 5:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			break;
		}

		CurrentItemIndex++;
	}
}