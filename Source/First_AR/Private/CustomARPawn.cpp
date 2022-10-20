// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "ARBlueprintLibrary.h"
#include "CustomARActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();

	// UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")),
	// true, true, FLinearColor::Red, 5);

	UARSessionConfig* Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);
}

// Called every frame
void ACustomARPawn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomARPawn::OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Screen Touched!")));

	FHitResult HitTestResult;
	
	// Perform a hit test, get the return values as HitTestResult
	if(!WorldHitTest(FVector2d(ScreenPos), HitTestResult))
	{
		// Hit test returned false
		UKismetSystemLibrary::PrintString(this, "Nothing Hit!", true, true, FLinearColor(0, 0.66, 1, 1), 2);
	}

	// Get object of the actor hit
	UClass* HitActorClass = UGameplayStatics::GetObjectClass(HitTestResult.GetActor());

	// If we've hit something
	if(UKismetMathLibrary::ClassIsChildOf(HitActorClass, ACustomARActor::StaticClass()))
	{
		UKismetSystemLibrary::PrintString(this, "Cube Pressed!", true, true, FLinearColor(0, 0.66, 1, 1), 2);
	}
}

bool ACustomARPawn::WorldHitTest(const FVector2d ScreenTouchLoc, FHitResult& HitResult)
{
	// Get player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	// Perform deprojection taking 2d clicker area and generating reference in 3d world space
	FVector WorldPos;
	FVector WorldDir;
	bool DeprojectionSuccess = UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenTouchLoc, WorldPos, WorldDir);

	// Construct line trace (raycast) vector (from point clicked to 1000 units beyond in the same direction)
	FVector TraceEndVec = WorldDir * 1000.0;
	TraceEndVec = WorldPos + TraceEndVec;

	// Perform line trace (raycast)
	bool TraceSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, WorldPos, TraceEndVec, ECollisionChannel::ECC_WorldDynamic);

	// Return if the operation was successful
	return TraceSuccess;
}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);	
}

