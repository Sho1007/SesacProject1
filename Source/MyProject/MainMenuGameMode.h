// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
class UMainMenuWidget;
UCLASS()
class MYPROJECT_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UMainMenuWidget* MainMenuWidget;
};