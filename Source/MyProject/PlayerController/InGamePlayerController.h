// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
class UInGameWidget;
class AWeaponBase;
UCLASS()
class MYPROJECT_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ShowBoxWidget(int32 ItemCount);

private:
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	TArray<AWeaponBase*> WeaponArray;

	UInGameWidget* InGameWidget;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UInGameWidget> InGameWidgetClass;
};