// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/EnemyBase.h"
#include "BossBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABossBase : public AEnemyBase
{
	GENERATED_BODY()

	virtual void Respawn() override;
};
