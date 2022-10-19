// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARActor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACustomARActor::ACustomARActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	// Find the Cube Asset and assign it using C++ (Right click on object in the content browser to get Reference string
	const auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

	const auto MaterialAsset = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/StarterContent/Materials/CustomMat.CustomMat'"));
	//MyCustomMat = CreateDefaultSubobject<UMaterial>(TEXT("My Material"));
	StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);

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

	// Print location every 2 secs
	if(TimeSinceLastPrint > 2)
	{
		TimeSinceLastPrint = 0;
		
		UKismetSystemLibrary::PrintString(this, FString(TEXT("Actor Location: ") + GetActorLocation().ToString()),
			true, true, FLinearColor::Red, 5);
	}
	
	float Scale = 2.0f / (3.0f - cos(2.0f * TotalTime));
	float Xpos = Scale * cos(TotalTime);
	float Ypos = 0.0f;
	float Zpos = Scale * sin(2.0f * TotalTime) / 2.0f;
	
	//FVector4 RelativeLocation = FVector4(GetActorLocation().X + Xpos, GetActorLocation().Y + Ypos, GetActorLocation().Z + Zpos);
	//FVector4 RelativeLocation = FVector4(Xpos, Ypos, Zpos);

	FMatrix Mat_Init = FMatrix::Identity;
	Mat_Init.M[3][0] = InitialLocation.X;
	Mat_Init.M[3][1] = InitialLocation.Y;
	Mat_Init.M[3][2] = InitialLocation.Z;
	
	// FMatrix Mat_Moving = FMatrix::Identity;
	// Mat_Moving.M[3][0] = RelativeLocation.X;
	// Mat_Moving.M[3][1] = RelativeLocation.Y;
	// Mat_Moving.M[3][2] = RelativeLocation.Z;

	// FMatrix Mat_Moving = FMatrix::Identity;
	// Mat_Moving.M[3][0] = GetActorLocation().X + Xpos;
	// Mat_Moving.M[3][1] = GetActorLocation().Y + Ypos;
	// Mat_Moving.M[3][2] = GetActorLocation().Z + Zpos;

	float MatScale = 400;

	FMatrix Mat_Moving = FMatrix::Identity;
	Mat_Moving.M[3][0] = Xpos * MatScale;
	Mat_Moving.M[3][1] = Ypos * MatScale;
	Mat_Moving.M[3][2] = Zpos * MatScale;
	
	
	FMatrix Mat_Final = Mat_Moving * Mat_Init;
	
	SetActorTransform(FTransform(Mat_Final));
	
	//SetActorLocation((RelativeLocation));

	Super::Tick(DeltaTime);
}

void ACustomARActor::PostInitializeComponents()
{
	InitialLocation = GetActorLocation();	
	
	Super::PostInitializeComponents();
}

