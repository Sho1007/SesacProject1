// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/EquipmentBase.h"
#include "Mask.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMask : public AEquipmentBase
{
	GENERATED_BODY()

public:
	virtual void Attach(AActor* OwningCharacter) override;
	virtual void LevelUp() override;
};