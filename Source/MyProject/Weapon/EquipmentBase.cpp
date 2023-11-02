// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/EquipmentBase.h"
#include "MyProject/Character/StatusComponent.h"

// Sets default values
AEquipmentBase::AEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEquipmentBase::LevelUp()
{
	CurrentLevel++;
}

// Called when the game starts or when spawned
void AEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEquipmentBase::Attach(AActor* OwningCharacter)
{
	AttachToActor(OwningCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	StatusComponent = Cast<UStatusComponent>(OwningCharacter->GetComponentByClass(UStatusComponent::StaticClass()));

	if (StatusComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AEquipmentBase::Attach) Player has no Status Component"));
	}
}

void AEquipmentBase::Dettach()
{

}

int32 AEquipmentBase::GetCurrentLevel() const
{
	return CurrentLevel;
}

int32 AEquipmentBase::GetMaxLevel() const
{
	return MaxLevel;
}

bool AEquipmentBase::IsEnforcable() const
{
	return CurrentLevel < MaxLevel;
}

FName AEquipmentBase::GetEquipmentName() const
{
	return EquipmentName;
}