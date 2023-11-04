// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UWidgetSwitcher;
UCLASS()
class MYPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
private:
	UPROPERTY(Transient, Meta = (AllowPrivateAccess, BindWidgetAnim))
	UWidgetAnimation* BlinkPressKeyText;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UWidgetSwitcher* WS_PressKey;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	USoundBase* IntroSound;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	USoundBase* ButtonInSound;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	USoundBase* ButtonOutSound;
};