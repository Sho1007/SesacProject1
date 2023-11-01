// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
class UBoxWidget;
class ULevelUpWidget;
UCLASS()
class MYPROJECT_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowBoxWidget(const TArray<FName>& ItemNameArray);

	void ShowLevelUpWidget(const TArray<FName>& ItemNameArray);
	void HideLevelUpWidget();

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;
private:
	UPROPERTY(Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* LevelUpAnimation;

	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBoxWidget* BoxWidget;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	ULevelUpWidget* LevelUpWidget;
};