// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameMode.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "CustomARActor.h"

ACustomGameMode::ACustomGameMode()
{
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();

	// Uncommenting this and building causes UE to crash!????????
	//Score = GetGameState<ACustomGameState>()->Score;

	PrimaryActorTick.bCanEverTick = true;
}

void ACustomGameMode::StartPlay()
{	
	// This is called before any BeginPlay
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Score: %d"), GetScore()));

	Super::StartPlay();

	SpawnCube();
	GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);

	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector CamerForward = CameraManager->GetCameraRotation().Vector();
}

int32 ACustomGameMode::GetScore()
{
	return GetGameState<ACustomGameState>()->Score;
}

void ACustomGameMode::SpawnCube()
{
	const FActorSpawnParameters SpawnInfo;
	const FVector MyLoc(900, 0, 0);
	const FRotator MyRot(0, 0, 0);
	ACustomARActor* CustomARActor = GetWorld()->SpawnActor<ACustomARActor>(MyLoc, MyRot, SpawnInfo);
}
