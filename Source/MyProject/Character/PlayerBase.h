// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class UInventoryComponent;
class UStatusComponent;
class UGameOverWidget;
UCLASS()
class MYPROJECT_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void Die();

public:
	UFUNCTION(BlueprintCallable)
	void AddExp(float NewExp);
	void LevelUp();

protected:
	// GameOver
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentExp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxExp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentLevel;

	// Component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInventoryComponent* InventoryComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatusComponent* StatusComponent;

public:
	DECLARE_DELEGATE_TwoParams(FDele_Single_Two_Float_Float, float, float);
	FDele_Single_Two_Float_Float OnExpUpdated;
	DECLARE_DELEGATE_OneParam(FDele_Single_One_Int, int32);
	FDele_Single_One_Int OnLevelUpdated;
};