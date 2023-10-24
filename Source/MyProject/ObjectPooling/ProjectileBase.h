// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ObjectPooling/PoolingActor.h"
#include "ProjectileBase.generated.h"

/**
 * 
 */
class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class MYPROJECT_API AProjectileBase : public APoolingActor
{
	GENERATED_BODY()

	AProjectileBase();

public:
	UFUNCTION()
	void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	int32 PenetrateCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	USphereComponent* HitBox;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float Speed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float Damage;
};