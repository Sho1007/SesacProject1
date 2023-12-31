// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/PoolingActor.h"

// Sets default values
APoolingActor::APoolingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APoolingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APoolingActor::IsActive() const
{
	return bIsActivated;
}

void APoolingActor::Activate()
{
	bIsActivated = true;
	SetActorTickEnabled(bIsActivated);
}

void APoolingActor::Deactivate()
{
	bIsActivated = false;
	SetActorTickEnabled(bIsActivated);
}

void APoolingActor::Init(ASpawnManager* NewSpawnManager, int32 NewPoolingIndex)
{
	SpawnManager = NewSpawnManager;

	PoolingIndex = NewPoolingIndex;
}