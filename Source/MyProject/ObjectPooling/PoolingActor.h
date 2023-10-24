// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolingActor.generated.h"

class ASpawnManager;
UCLASS()
class MYPROJECT_API APoolingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsActive() const;

	virtual void Activate();
	virtual void Deactivate();

	virtual void Init(ASpawnManager* NewSpawnManager, int32 NewPoolingIndex);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "PoolingActor", Meta = (AllowPrivateAccess))
	int32 PoolingIndex;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "PoolingActor", Meta = (AllowPrivateAccess))
	bool bIsActivated;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "PoolingActor", Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
};