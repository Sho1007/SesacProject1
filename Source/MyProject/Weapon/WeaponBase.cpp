// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/WeaponBase.h"

#include <GameFramework/Character.h>
#include <EngineUtils.h>

#include "../Character/StatusComponent.h"
#include "../ObjectPooling/SpawnManager.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWeaponBase::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::Attack"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAttackCoolTime += DeltaTime;

	if (CurrentAttackCoolTime >= AttackCoolTime)
	{
		CurrentAttackCoolTime -= AttackCoolTime;
		Attack();
	}
}

bool AWeaponBase::IsPossibleToLevelUp() const
{
	return CurrentLevel < MaxLevel;
}

int AWeaponBase::GetCurrentLevel() const
{
	return CurrentLevel;
}

int AWeaponBase::GetMaxLevel() const
{
	return MaxLevel;
}

FName AWeaponBase::GetWeaponName() const
{
	return WeaponName;
}

void AWeaponBase::Attach(AActor* OwningCharacter)
{
	// Set SpawnManager
	TActorIterator<AActor> It(GetWorld(), ASpawnManager::StaticClass());
	SpawnManager = Cast<ASpawnManager>(*It);

	if (SpawnManager == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ADagger::Attach) SpawnManager is nullptr"));
	}

	// Set StatusComponent
	if (UStatusComponent* NewStatusComponent = Cast<UStatusComponent>(OwningCharacter->GetComponentByClass(UStatusComponent::StaticClass())))
	{
		StatusComponent = NewStatusComponent;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponBase::Attach) Player has no Status Component"));
	}
}

void AWeaponBase::LevelUp()
{
	CurrentLevel++;
}