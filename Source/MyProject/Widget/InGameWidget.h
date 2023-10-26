// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
class UBoxWidget;
UCLASS()
class MYPROJECT_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowBoxWidget();
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UBoxWidget* BoxWidget;
};