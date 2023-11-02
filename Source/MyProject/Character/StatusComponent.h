// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Multi_One_Float, float);
DECLARE_DELEGATE_OneParam(FDele_Multi_One_Int, int32);


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

	UFUNCTION(CallInEditor)
	void TestAdd();

	UPROPERTY(EditAnywhere)
	float TestValue;
	UPROPERTY(EditAnywhere)
	FName TestType;
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
	int32 GetAmount() const;
	float GetCooldown() const;

	float GetLuck() const;
	float GetGrowth() const;
	float GetGreed() const;
	float GetMagnet() const;


private:
	// �ִ� ü�� - �⺻ 100
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float MaxHealth = 100;
	// ȸ�� - �⺻ 0
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Recovery;
	// ���� - �⺻ 0
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Armor;
	// �̵��ӵ� % - �⺻ 1
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float MoveSpeed = 1;

	// ���ط� % - �⺻ 1 �ִ� 10
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Might = 1;
	// ���� ���� % - �⺻ 1 �ִ� 10
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Area = 1;
	// ����ü �ӵ� % �⺻ 1 �ִ� 5
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Speed = 1;
	// ���� �ð� % �⺻ 1 �ִ� 5
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Duration = 1;
	// ����ü �� - �⺻ 0 �ִ� 10
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	int32 Amount = 0;
	// ��Ÿ�� % �⺻ 0 �ִ� 0.9
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Cooldown = 0;

	// ��� % - �⺻ 1
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Luck = 1;
	// ���� % - �⺻ 1 (����ġ �ۼ�Ʈ)
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Growth = 1;
	// Ž�� % - �⺻ 1 (�⺻��ġ + �߰� �ɷ�ġ) * �������� ��� ���ʽ�
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Greed = 1;
	// �ڼ� % - �⺻ 30 Todo : �굵 100 ���� ������ 0.3���� �ٲ���ϳ�?
	UPROPERTY(EditAnywhere, Category = "Status", Meta = (AllowPrivateAccess))
	float Magnet = 30;

public:
	
	// Delegate
	FDele_Multi_One_Float OnMaxHealthUpdated;
	FDele_Multi_One_Float OnRecoveryUpdated;
	FDele_Multi_One_Float OnArmorUpdated;
	FDele_Multi_One_Float OnMoveSpeedUpdated;

	FDele_Multi_One_Float OnMightUpdated;
	FDele_Multi_One_Float OnAreaUpdated;
	FDele_Multi_One_Float OnSpeedUpdated;
	FDele_Multi_One_Float OnDurationUpdated;
	FDele_Multi_One_Int OnAmountUpdated;
	FDele_Multi_One_Float OnCooldownUpdated;

	FDele_Multi_One_Float OnLuckUpdated;
	FDele_Multi_One_Float OnGrowthUpdated;
	FDele_Multi_One_Float OnGreedUpdated;
	FDele_Multi_One_Float OnMagnetUpdated;
};