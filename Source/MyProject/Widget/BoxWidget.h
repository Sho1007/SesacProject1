// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxWidget.generated.h"

/**
 * 
 */
class UBorder;
class UImage;
class UButton;
UCLASS()
class MYPROJECT_API UBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void ShowWidget(const TArray<FName>& NewItemNameArray);
	void HideWidget();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;

	UFUNCTION()
	void OnOpenBoxButtonClicked();

	UFUNCTION()
	void SetItemImage();
private:
	FTimerHandle SetItemImageTimerHandle;
	int CurrentItemIndex;
	TArray<FName> ItemNameArray;

	// Time
	bool bIsSetItemImage;
	float CurrentSetItemImageTime;

	bool bIsDelay;
	float CurrentDelayTime;

	// Animation
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* BoxAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* Item1Animation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* Item3Animation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* Item5Animation;

	// Image
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Item1;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Item2;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Item3;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Item4;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_Item5;

	// Border
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBorder* Brd_Item1;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBorder* Brd_Item2;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBorder* Brd_Item3;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBorder* Brd_Item4;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBorder* Brd_Item5;

	// Button
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UButton* Btn_OpenBox;
};