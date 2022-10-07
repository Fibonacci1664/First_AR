// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARActor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACustomARActor::ACustomARActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	TotalTime = 0.0f;
	TimeSinceLastPrint = 0;
}

// Called when the game starts or when spawned
void ACustomARActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomARActor::Tick(float DeltaTime)
{
	TotalTime += DeltaTime;
	TimeSinceLastPrint += DeltaTime;
	
	Super::Tick(DeltaTime);

	// Print location every 2 secs
	if(TimeSinceLastPrint > 2)
	{
		TimeSinceLastPrint = 0;
		
		UKismetSystemLibrary::PrintString(this, FString(TEXT("Actor Location: ") + GetActorLocation().ToString()),
			true, true, FLinearColor::Red, 5);
	}
	
	const float Scale = 2.0f / (3.0f - cos(2.0f * TotalTime));
	const float Xpos = Scale * cos(TotalTime);
	const float Zpos = Scale * sin(2.0f * TotalTime) / 2.0f;
	
	const FVector4 NewPos = FVector4(GetActorLocation().X + Xpos, GetActorLocation().Y + 0.0f, GetActorLocation().Z + Zpos);

	SetActorLocation((NewPos));
}

