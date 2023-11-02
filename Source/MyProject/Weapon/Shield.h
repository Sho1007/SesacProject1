// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/EquipmentBase.h"
#include "Shield.generated.h"

/**
 * 
 */

// Todo : ���� ��ȭ�ؼ� ���� + ��� �� ������ٸ�, ����� ���� �ɷ�ġ�� ���� ������°�?
// Todo : ������ٸ�, ����� ���� �ɷ�ġ�� ���� �����س��ٰ�, ��ȭ �� ����߰ڴ�.
UCLASS()
class MYPROJECT_API AShield : public AEquipmentBase
{
	GENERATED_BODY()

public:
	virtual void Attach(AActor* OwningCharacter) override;
	virtual void LevelUp() override;
};