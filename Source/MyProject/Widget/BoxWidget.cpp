// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BoxWidget.h"

#include <Components/Image.h>
#include <Components/Border.h>
#include <Components/Button.h>

#include <Animation/UMGSequencePlayer.h>
#include <Animation/WidgetAnimation.h>

#include "../Inventory/InventoryComponent.h"
#include "../ZombieSurvivalGameInstance.h"
#include "../ObjectPooling/ItemBase.h"


bool UBoxWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (Item1Animation) Item1Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;
	if (Item3Animation) Item3Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;
	if (Item5Animation) Item5Animation->DefaultCompletionMode = EMovieSceneCompletionMode::RestoreState;

	Btn_OpenBox->OnClicked.AddDynamic(this, &UBoxWidget::OnOpenBoxButtonClicked);

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
	PlayAnimation(BoxAnimation);
}

void UBoxWidget::HideWidget()
{
	bIsSetItemImage = false;
	CurrentSetItemImageTime = 0.0f;
	bIsDelay = false;
	CurrentDelayTime = 0.0f;

	Img_Item1->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item2->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item3->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item4->SetVisibility(ESlateVisibility::Collapsed);
	Img_Item5->SetVisibility(ESlateVisibility::Collapsed);

	Brd_Item1->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Item2->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Item3->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Item4->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Item5->SetVisibility(ESlateVisibility::Collapsed);

	StopAllAnimations();

	SetVisibility(ESlateVisibility::Collapsed);

	GetOwningPlayer()->SetPause(false);
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	GetOwningPlayer()->SetShowMouseCursor(false);
}

void UBoxWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::NativeTick"));

	if (bIsSetItemImage)
	{
		CurrentSetItemImageTime += InDeltaTime;

		//UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::NativeTick) CurrentSetItemImageTime : %f"), CurrentSetItemImageTime);

		if (CurrentSetItemImageTime >= 0.3f)
		{
			CurrentSetItemImageTime -= 0.3f;
			SetItemImage();
		}
	}

	if (bIsDelay)
	{
		CurrentDelayTime += InDeltaTime;

		if (CurrentDelayTime >= 1.0f)
		{
			HideWidget();
		}
	}
}

void UBoxWidget::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	if (Player.GetAnimation() == BoxAnimation)
	{
		Btn_OpenBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CurrentItemIndex = 0;
		bIsSetItemImage = true;
	}

	//UE_LOG(LogTemp, Warning, TEXT("UBoxWidget::OnAnimationFinishedPlaying"));
}

void UBoxWidget::OnOpenBoxButtonClicked()
{
	switch (ItemNameArray.Num())
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

	Btn_OpenBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UBoxWidget::SetItemImage()
{
	if (ItemNameArray.Num() == CurrentItemIndex)
	{
		bIsDelay = true;
	}
	else
	{
		UZombieSurvivalGameInstance* GameInstance = GetGameInstance<UZombieSurvivalGameInstance>();
		check(GameInstance);

		UTexture2D* ItemImage = nullptr;
		if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass())))
		{
			if (InventoryComponent->AddWeapon(ItemNameArray[CurrentItemIndex]))
			{
				// GameInstance 에서 DataTable 찾아서 FItemData 에서 Weapon Image 읽어오기
				FWeaponData* WeaponData = GameInstance->GetWeaponData(ItemNameArray[CurrentItemIndex]);
				check(WeaponData);
				ItemImage = WeaponData->WeaponImage;
			}
			else
			{
				// GameInstance 에서 DataTable 찾아서 FItemData 에서 Money Image 읽어오기
				// Todo : ObjectPooling 상속 받아서 ItemBase 만들기
				FItemData* ItemData = GameInstance->GetItemData(TEXT("Money"));
				check(ItemData);
				ItemImage = ItemData->ItemImage;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Player has no Inventory Component"));
		}

		if (ItemImage == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) %s ItemImage is nullptr"), *ItemNameArray[CurrentItemIndex].ToString());
		}

		switch (CurrentItemIndex)
		{
		case 0:
			Img_Item1->SetBrushFromTexture(ItemImage);
			Img_Item1->SetVisibility(ESlateVisibility::Visible);
			Brd_Item1->SetVisibility(ESlateVisibility::Visible);
			//UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Item1 Image Setted"));
			break;
		case 1:
			Img_Item2->SetBrushFromTexture(ItemImage);
			Img_Item2->SetVisibility(ESlateVisibility::Visible);
			Brd_Item2->SetVisibility(ESlateVisibility::Visible);
			//UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Item2 Image Setted"));
			break;
		case 2:
			Img_Item3->SetBrushFromTexture(ItemImage);
			Img_Item3->SetVisibility(ESlateVisibility::Visible);
			Brd_Item3->SetVisibility(ESlateVisibility::Visible);
			//UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Item3 Image Setted"));
			break;
		case 3:
			Img_Item4->SetBrushFromTexture(ItemImage);
			Img_Item4->SetVisibility(ESlateVisibility::Visible);
			Brd_Item4->SetVisibility(ESlateVisibility::Visible);
			//UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Item4 Image Setted"));
			break;
		case 4:
			Img_Item5->SetBrushFromTexture(ItemImage);
			Img_Item5->SetVisibility(ESlateVisibility::Visible);
			Brd_Item5->SetVisibility(ESlateVisibility::Visible);
			//UE_LOG(LogTemp, Error, TEXT("UBoxWidget::SetItemImage) Item5 Image Setted"));
			break;
		}

		CurrentItemIndex++;
	}
}
