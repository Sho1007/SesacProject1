// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusComponent::TestAdd()
{
	if (TestType == TEXT("MaxHealth"))
	{
		SetMaxHealth(TestValue);
	}
	else if (TestType == TEXT("Recovery"))
	{
		SetRecovery(TestValue);
	}
	else if (TestType == TEXT("Armor"))
	{
		SetArmor(TestValue);
	}
	else if (TestType == TEXT("MoveSpeed"))
	{
		SetMoveSpeed(TestValue);
	}
	else if (TestType == TEXT("Might"))
	{
		SetMight(TestValue);
	}
	else if (TestType == TEXT("Area"))
	{
		SetArea(TestValue);
	}
	else if (TestType == TEXT("Speed"))
	{
		SetSpeed(TestValue);
	}
	else if (TestType == TEXT("Duration"))
	{
		SetDuration(TestValue);
	}
	else if (TestType == TEXT("Amount"))
	{
		SetAmount((int32)TestValue);
	}
	else if (TestType == TEXT("Cooldown"))
	{
		SetCooldown(TestValue);
	}
}

void UStatusComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;

	OnMaxHealthUpdated.Broadcast(MaxHealth);
}

void UStatusComponent::SetRecovery(float NewRecovery)
{
	Recovery = NewRecovery;

	OnRecoveryUpdated.Broadcast(Recovery);
}

void UStatusComponent::SetArmor(float NewArmor)
{
	Armor = NewArmor;

	OnArmorUpdated.Broadcast(Armor);
}

void UStatusComponent::SetMoveSpeed(float NewMoveSpeed)
{
	MoveSpeed = NewMoveSpeed;

	OnMoveSpeedUpdated.Broadcast(MoveSpeed);
}

void UStatusComponent::SetMight(float NewMight)
{
	if (NewMight > 10.0f) NewMight = 10.0f;
	Might = NewMight;

	OnMightUpdated.Broadcast(Might);
}

void UStatusComponent::SetArea(float NewArea)
{
	if (NewArea > 10.0f) NewArea = 10.0f;
	Area = NewArea;

	OnAreaUpdated.Broadcast(Area);
}

void UStatusComponent::SetSpeed(float NewSpeed)
{
	if (NewSpeed > 5.0f) NewSpeed = 5.0f;
	Speed = NewSpeed;
	UE_LOG(LogTemp, Warning, TEXT("UStatusComponent::SetSpeed) StatusComponent : %s"), *this->GetName());

	OnSpeedUpdated.Broadcast(Speed);
}

void UStatusComponent::SetDuration(float NewDuration)
{
	if (NewDuration > 5.0f) NewDuration = 5.0f;
	Duration = NewDuration;

	OnDurationUpdated.Broadcast(Duration);
}

void UStatusComponent::SetAmount(float NewAmount)
{
	if (NewAmount > 10) NewAmount = 10;
	Amount = NewAmount;
	OnAmountUpdated.Broadcast(Amount);
}

void UStatusComponent::SetCooldown(float NewCooldown)
{
	if (NewCooldown > 0.9f) NewCooldown = 0.9f;
	Cooldown = NewCooldown;

	OnCooldownUpdated.Broadcast(Cooldown);
}

void UStatusComponent::SetLuck(float NewLuck)
{
	Luck = NewLuck;

	OnLuckUpdated.Broadcast(Luck);
}

void UStatusComponent::SetGrowth(float NewGrowth)
{
	Growth = NewGrowth;

	OnGrowthUpdated.Broadcast(Growth);
}

void UStatusComponent::SetGreed(float NewGreed)
{
	Greed = NewGreed;

	OnGreedUpdated.Broadcast(Greed);
}

void UStatusComponent::SetMagnet(float NewMagnet)
{
	Magnet = NewMagnet;

	OnMagnetUpdated.Broadcast(Magnet);
}

float UStatusComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UStatusComponent::GetRecovery() const
{
	return Recovery;
}

float UStatusComponent::GetArmor() const
{
	return Armor;
}

float UStatusComponent::GetMoveSpeed() const
{
	return MoveSpeed;
}

float UStatusComponent::GetMight() const
{
	return Might;
}

float UStatusComponent::GetArea() const
{
	return Area;
}

float UStatusComponent::GetSpeed() const
{
	return Speed;
}

float UStatusComponent::GetDuration() const
{
	return Duration;
}

int32 UStatusComponent::GetAmount() const
{
	return Amount;
}

float UStatusComponent::GetCooldown() const
{
	return Cooldown;
}

float UStatusComponent::GetLuck() const
{
	return Luck;
}

float UStatusComponent::GetGrowth() const
{
	return Growth;
}

float UStatusComponent::GetGreed() const
{
	return Greed;
}

float UStatusComponent::GetMagnet() const
{
	return Magnet;
}