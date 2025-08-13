// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create CapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CapsuleComponent;

	//Create SkeletalMesh
	SkeletonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	//Create FloatingPawnMovement
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	//Create IndicateStaticMeshComponent;
	IndicateStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IndicateStaticMeshComponent"));

	//Attach Components
	SkeletonMeshComponent->SetupAttachment(RootComponent);
	IndicateStaticMeshComponent->SetupAttachment(RootComponent);

	//Set IndicateStaticMeshComponent Property
	IndicateStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IndicateStaticMeshComponent->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::SetIndicateShow(const bool IsShow)
{
	IndicateStaticMeshComponent->SetHiddenInGame(!IsShow);
}

