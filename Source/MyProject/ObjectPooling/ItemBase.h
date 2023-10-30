// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ObjectPooling/PoolingActor.h"

#include <Engine/DataTable.h>

#include "ItemBase.generated.h"

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* ItemMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemImage;
};

UCLASS()
class MYPROJECT_API AItemBase : public APoolingActor
{
	GENERATED_BODY()
	
};