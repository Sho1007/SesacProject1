// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MainMenuWidget.h"

#include <Components/WidgetSwitcher.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(IntroSound);

	PlaySound(IntroSound);

	PlayAnimation(BlinkPressKeyText, 0, 0);

	// Set PC 
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(GetCachedWidget());

	APlayerController* PC = GetOwningPlayer();

	check(PC);
	
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(false);
}

FReply UMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (Super::NativeOnKeyDown(InGeometry, InKeyEvent).IsEventHandled()) return FReply::Handled();

	//UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::NativeOnKeyDown) Pressed Key : %s"), *InKeyEvent.GetKey().ToString());

	if (WS_PressKey->GetActiveWidgetIndex() == 0)
	{
		PlaySound(ButtonInSound);

		WS_PressKey->SetActiveWidgetIndex(1);
			
		StopAnimation(BlinkPressKeyText);

		return FReply::Handled();
	}

	return FReply::Unhandled();
}