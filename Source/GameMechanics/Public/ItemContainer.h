// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "ItemContainer.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemGroupStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items Group")
	TArray<UItem*> Items;
};


UCLASS(BlueprintType)
class GAMEMECHANICS_API UItemContainer : public UObject
{
	GENERATED_BODY()
	
public:
	void AddItem(UItem* item);
	void RemoveItem(FName itemName, int pos);
	void RemoveItem(UItem* item);
	TArray<UItem*> GetAllItems();

private:
	TMap<FName, FItemGroupStruct*> Items;
	
	
};
