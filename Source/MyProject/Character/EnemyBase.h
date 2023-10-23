// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../ObjectPooling/PoolingActor.h"

#include "EnemyBase.generated.h"

UENUM()
enum class EEnemyState : uint8 
{
	NONE,
	IDLE,
	CHASE,
	ATTACK,
	SIZE,
};

class USkeletalMeshComponent;
class UCapsuleComponent;
UCLASS()
class MYPROJECT_API AEnemyBase : public APoolingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	virtual void Die();
	virtual void Attack();
private:
	void AvoidObstacle(FVector& MoveDirection);

	UFUNCTION(BlueprintCallable)
	void CheckHit();
	UFUNCTION(BlueprintCallable)
	void EndAttack();

	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage = nullptr);
	

private:
	// Montage
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UAnimMontage* AttackMontage;

	// FSM
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float Speed;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	bool bIsAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float AttackRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float AttackDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	ACharacter* TargetCharacter;
	
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	EEnemyState EnemyState;



	// ObstacleCheck
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float ObstacleCheckDistance;

	// Component
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UCapsuleComponent* CapsuleComponent;
};