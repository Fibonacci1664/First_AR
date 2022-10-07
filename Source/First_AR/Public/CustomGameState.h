// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_AR_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACustomGameState();
	virtual ~ACustomGameState() = default;

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(const int32 NewScore);

	int32 Score;
};
