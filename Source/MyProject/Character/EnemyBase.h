// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
class MYPROJECT_API AEnemyBase : public AActor
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

private:
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	EEnemyState EnemyState;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy", Meta = (AllowPrivateAccess))
	UCapsuleComponent* CapsuleComponent;
};