// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExpBarWidget.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;
UCLASS()
class MYPROJECT_API UExpBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateExp(float CurrentExp, float MaxExp);
	UFUNCTION()
	void UpdateLevel(int32 CurrentLevel);
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UProgressBar* PrgBar_ExpBar;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_Level;
};