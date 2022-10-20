// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CustomARPawn.generated.h"

UCLASS()
class FIRST_AR_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos);
	bool WorldHitTest(FVector2d ScreenTouchLoc, FHitResult& HitResult);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "SceneComponent", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(Category = "CameraComponent", VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

};
