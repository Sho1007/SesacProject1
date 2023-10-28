// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxWidget.generated.h"

/**
 * 
 */
class UImage;
UCLASS()
class MYPROJECT_API UBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void ShowWidget(const TArray<FName>& NewItemNameArray);
	void HideWidget();

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;

	UFUNCTION()
	void SetItemImage();
private:
	FTimerHandle SetItemImageTimerHandle;
	int CurrentItemIndex;
	TArray<FName> ItemNameArray;

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

};