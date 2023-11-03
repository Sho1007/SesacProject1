// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ObjectPooling/PoolingActor.h"
#include <Engine/DataTable.h>
#include "ProjectileBase.generated.h"

/**
 * 
 */

class UStaticMesh;
USTRUCT(BlueprintType)
struct FProjectileData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MeshScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator MeshRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial* Material;
};

class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class MYPROJECT_API AProjectileBase : public APoolingActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

	UFUNCTION()
	void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetProjectileData(FProjectileData* NewProjectileData, float NewSpeed, float NewDamage, float NewPierce, float NewArea, float NewKnockback);

	virtual void Attack(AActor* TargetActor);

	virtual void Activate() override;
	virtual void Deactivate() override;

	float GetSpeed() const;

	float GetKnockback() const;

protected:
	void Move(float DeltaTime);

protected:
	// AvoidMultiHit
	TArray<AActor*> HitActorArray;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	USoundBase* ProjectileSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float BaseDistance = 200.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float BaseSpeed = 200.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float Distance;
	float CurrentDistance;
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
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Projectile", Meta = (AllowPrivateAccess))
	float Knockback;
};