// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ZombieSurvivalSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UZombieSurvivalSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UZombieSurvivalSaveGame();

public:
	// Getter
	const FString& GetSaveSlotName() const;
	int32 GetUserIndex() const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "SaveGame", Meta = (AllowPrivateAccess))
	int32 Coin;

	// Save Slot Info
	UPROPERTY(EditDefaultsOnly, Category = "SaveGame", Meta = (AllowPrivateAccess))
	FString SaveSlotName;
	UPROPERTY(EditDefaultsOnly, Category = "SaveGame", Meta = (AllowPrivateAccess))
	int32 UserIndex;
};