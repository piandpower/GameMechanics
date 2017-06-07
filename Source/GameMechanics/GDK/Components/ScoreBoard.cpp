// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreBoard.h"


// Sets default values for this component's properties
UScoreBoard::UScoreBoard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoreBoard::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScoreBoard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScoreBoard::AddRecord(FScoreBoardRecord record)
{
	//Board.Add(record);
	Board.FindOrAdd(record.ScoreOwner).FindOrAdd(record.ScoreTarget).Add(record);
	ScoreBoardUpdated.Broadcast(record);
}

void UScoreBoard::ClearBoard()
{
	Board.Empty();
}

int UScoreBoard::GetScore(FName scoreOwner)
{
	if (!Board.Contains(scoreOwner))
		return 0;

	int result = 0;
	for (const auto& Entry : Board[scoreOwner])
	{
		for (FScoreBoardRecord record : Entry.Value)
		{
			result += record.Score;
		}
	}
	return result;
}

int UScoreBoard::GetScoreByTarget(FName scoreOwner, FName scoreTarget)
{
	if (!Board.Contains(scoreOwner))
		return 0;

	if (!Board.Find(scoreOwner)->Contains(scoreTarget))
		return 0;

	int result = 0;
	for (FScoreBoardRecord record : Board[scoreOwner][scoreTarget])
	{
		result += record.Score;
	}

	return result;
}

int UScoreBoard::GetKillsCount(FName scoreOwner)
{
	if (!Board.Contains(scoreOwner))
		return 0;

	int result = 0;
	for (const auto& Entry : Board[scoreOwner])
	{
		for (FScoreBoardRecord record : Entry.Value)
		{
			if (record.bIsKilled) result++;
		}
	}
	return result;
}

int UScoreBoard::GetKillsCountByTarget(FName scoreOwner, FName scoreTarget)
{
	if (!Board.Contains(scoreOwner))
		return 0;

	if (!Board.Find(scoreOwner)->Contains(scoreTarget))
		return 0;

	int result = 0;
	for (FScoreBoardRecord record : Board[scoreOwner][scoreTarget])
	{
		if (record.bIsKilled) result++;
	}

	return result;
}

TArray<FName> UScoreBoard::GetTargets(FName scoreOwner)
{
	if (!Board.Contains(scoreOwner))
		return TArray<FName>();
	
	TArray<FName> result;
	Board[scoreOwner].GenerateKeyArray(result);
	return result;
}



