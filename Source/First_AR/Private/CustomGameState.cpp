// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameState.h"


ACustomGameState::ACustomGameState()
{
	Score = 0;
}

int32 ACustomGameState::GetScore()
{
	return Score;
}

void ACustomGameState::SetScore(const int32 NewScore)
{
	Score = NewScore;
}
