// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_One_Float, float);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Setter
	void SetMaxHealth(float NewMaxHealth);
	void SetRecovery(float NewRecovery);
	void SetArmor(float NewArmor);
	void SetMoveSpeed(float NewMoveSpeed);

	void SetMight(float NewMight);
	void SetArea(float NewArea);
	void SetSpeed(float NewSpeed);
	void SetDuration(float NewDuration);
	void SetAmount(float NewAmount);
	void SetCooldown(float NewCooldown);

	void SetLuck(float NewLuck);
	void SetGrowth(float NewGrowth);
	void SetGreed(float NewGreed);
	void SetMagnet(float NewMagnet);

	// Getter

	float GetMaxHealth() const;
	float GetRecovery() const;
	float GetArmor() const;
	float GetMoveSpeed() const;

	float GetMight() const;
	float GetArea() const;
	float GetSpeed() const;
	float GetDuration() const;
	float GetAmount() const;
	float GetCooldown() const;

	float GetLuck() const;
	float GetGrowth() const;
	float GetGreed() const;
	float GetMagnet() const;


private:
	// 최대 체력 - 기본 100
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float MaxHealth = 100;
	// 회복 - 기본 0
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Recovery;
	// 방어력 - 기본 0
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Armor;
	// 이동속도 % - 기본 100
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float MoveSpeed = 100;

	// 피해량 % - 기본 100 최대 1000
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Might = 100;
	// 공격 범위 % - 기본 100 최대 1000
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Area = 100;
	// 투사체 속도 % 기본 100 최대 500
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Speed = 100;
	// 지속 시간 % 기본 100 최대 500
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Duration = 100;
	// 투사체 수 - 기본 0 최대 10
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Amount;
	// 쿨타임 % 기본 100 최소! 10
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Cooldown = 100;

	// 행운 % - 기본 100
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Luck = 100;
	// 성장 % - 기본 100 (경험치 퍼센트)
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Growth = 100;
	// 탐욕 % - 기본 100 (기본수치 + 추가 능력치) * 스테이지 골드 보너스
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Greed = 100;
	// 자석 % - 기본 30
	UPROPERTY(EditDefaultsOnly, Category = "Status", Meta = (AllowPrivateAccess))
	float Magnet = 30;

public:
	/*
	// Delegate
	FDele_Multi_One_Float OnMaxHealthUpdated;
	FDele_Multi_One_Float OnRecoveryUpdated;
	FDele_Multi_One_Float OnArmorUpdated;
	FDele_Multi_One_Float OnMoveSpeedUpdated;

	FDele_Multi_One_Float OnMightUpdated;
	FDele_Multi_One_Float OnAreaUpdated;
	FDele_Multi_One_Float OnSpeedUpdated;
	FDele_Multi_One_Float OnDurationUpdated;
	FDele_Multi_One_Float OnAmountUpdated;
	FDele_Multi_One_Float OnCooldownUpdated;

	FDele_Multi_One_Float OnLuckUpdated;
	FDele_Multi_One_Float OnGrowthUpdated;
	FDele_Multi_One_Float OnGreedUpdated;
	FDele_Multi_One_Float OnMagnetUpdated;
	*/
};