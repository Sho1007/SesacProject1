// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/EquipmentBase.h"
#include "Shield.generated.h"

/**
 * 
 */

// Todo : 만약 진화해서 무기 + 장비 가 사라진다면, 장비의 증가 능력치도 같이 사라지는가?
// Todo : 사라진다면, 장비의 증가 능력치를 따로 저장해놨다가, 진화 시 빼줘야겠다.
// Todo : 현재까지는, 진화한다고 능력치 감소가 일어나지는 않는 것 같다.
UCLASS()
class MYPROJECT_API AShield : public AEquipmentBase
{
	GENERATED_BODY()

public:
	virtual void Attach(AActor* OwningCharacter) override;
	virtual void LevelUp() override;
};