// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/BossBase.h"

#include "MyProject/ObjectPooling/SpawnManager.h"

void ABossBase::Respawn()
{
	SpawnManager->RespawnBoss(PoolingIndex);
}