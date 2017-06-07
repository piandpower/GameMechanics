// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreBoard.generated.h"

/**
*
*/
USTRUCT(BlueprintType)
struct FScoreBoardRecord
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Board")
	FName ScoreOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Board")
	FName ScoreTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Board")
	int Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Board")
	bool bIsKilled;


	FScoreBoardRecord(FName playerName, FName Type, int score, bool InbKilled)
		: ScoreOwner(playerName)
		, ScoreTarget(Type)
		, Score(score)
		, bIsKilled(InbKilled)
	{
	}

	FScoreBoardRecord()
		: ScoreOwner(NAME_None)
		, ScoreTarget(NAME_None)
		, Score(0)
		, bIsKilled(false)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreUpdatedDelegate, FScoreBoardRecord, Record);

/**
*
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEMECHANICS_API UScoreBoard : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreBoard();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UFUNCTION(BlueprintCallable, Category = "Score Board")
	void AddRecord(FScoreBoardRecord record);

	UFUNCTION(BlueprintCallable, Category = "Score Board")
	void ClearBoard();

	UFUNCTION(BlueprintCallable, Category = "Score Board")
	int GetScore(FName scoreOwner);	

	UFUNCTION(BlueprintCallable, Category = "Score Board")
	int GetScoreByTarget(FName scoreOwner, FName scoreTarget);

	UFUNCTION(BlueprintCallable, Category = "Score Board")
	int GetKillsCount(FName scoreOwner);
	
	UFUNCTION(BlueprintCallable, Category = "Score Board")
	int GetKillsCountByTarget(FName scoreOwner, FName scoreTarget);

	UFUNCTION(BlueprintCallable, Category = "Score Board")
	TArray<FName> GetTargets(FName scoreOwner);

	UPROPERTY(BlueprintAssignable, Category = "Score Board")
	FScoreUpdatedDelegate ScoreBoardUpdated;
	

private:


	TMap<FName, TMap<FName, TArray<FScoreBoardRecord>>> Board;
};
