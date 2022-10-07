// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomARPawn.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_AR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;
};
