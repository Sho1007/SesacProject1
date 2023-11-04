// Fill out your copyright notice in the Description page of Project Settings.


#include "../SaveGame/ZombieSurvivalSaveGame.h"

UZombieSurvivalSaveGame::UZombieSurvivalSaveGame() : SaveSlotName(TEXT("DefaultSaveSlot")), UserIndex(0)
{
}

const FString& UZombieSurvivalSaveGame::GetSaveSlotName() const
{
	return SaveSlotName;
}

int32 UZombieSurvivalSaveGame::GetUserIndex() const
{
	return UserIndex;
}