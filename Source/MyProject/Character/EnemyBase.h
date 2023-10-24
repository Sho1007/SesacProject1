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
class UBoxComponent;
class USphereComponent;
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
	UFUNCTION()
	void OnMoveBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMoveBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void Die();
	virtual void Attack();

private:
	// Montage
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UAnimMontage* AttackMontage;

	// FSM
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float Speed;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	ACharacter* TargetCharacter;
	
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	EEnemyState EnemyState;

	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	FVector MoveDirection;


	// Attack
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float AttackCoolTime;
	float CurrentAttackCoolTime;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	bool bIsAttackable;

	// ObstacleCheck
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float ObstacleCheckDistance;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	TArray<UPrimitiveComponent*> ObstacleComponentArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy", Meta = (AllowPrivateAccess))
	float ImpulsePower;

	// Component
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UBoxComponent* MoveBoxComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UCapsuleComponent* CapsuleComponent;
};