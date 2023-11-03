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

	check(SpawnManager);

	// Set StatusComponent
	
	if (UStatusComponent* NewStatusComponent = Cast<UStatusComponent>(OwningCharacter->GetComponentByClass(UStatusComponent::StaticClass())))
	{
		StatusComponent = NewStatusComponent;
		StatusComponent->OnAreaUpdated.AddUObject(this, &AWeaponBase::UpdateArea);
		StatusComponent->OnAmountUpdated.AddUObject(this, &AWeaponBase::UpdateAmount);
		StatusComponent->OnSpeedUpdated.AddUObject(this, &AWeaponBase::UpdateSpeed);
		StatusComponent->OnMightUpdated.AddUObject(this, &AWeaponBase::UpdateMight);
		StatusComponent->OnDurationUpdated.AddUObject(this, &AWeaponBase::UpdateDuration);
		StatusComponent->OnCooldownUpdated.AddUObject(this, &AWeaponBase::UpdateCooldown);

		StatusArea = StatusComponent->GetArea();
		StatusAmount = StatusComponent->GetAmount();
		StatusSpeed = StatusComponent->GetSpeed();
		StatusMight = StatusComponent->GetMight();
		StatusDuration	= StatusComponent->GetDuration();
		StatusCooldown = StatusComponent->GetCooldown();
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

void AWeaponBase::UpdateAmount(int32 NewAmount)
{
	StatusAmount = NewAmount;
}

void AWeaponBase::UpdateArea(float NewArea)
{
	StatusArea = NewArea;
}

void AWeaponBase::UpdateSpeed(float NewSpeed)
{
	StatusSpeed = NewSpeed;
}

void AWeaponBase::UpdateMight(float NewMight)
{
	StatusMight = NewMight;
}

void AWeaponBase::UpdateDuration(float NewDuration)
{
	StatusDuration = NewDuration;
}

void AWeaponBase::UpdateCooldown(float NewCooldown)
{
	StatusCooldown = NewCooldown;
}