// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <AIController.h>

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create CapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCanEverAffectNavigation(false);

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
	IndicateStaticMeshComponent->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::OrientPawnToMoveDirection()
{
	if (!bMoving)
	{
		return;
	}

	FVector MoveDirction = FVector(MoveTargetLocation.X - GetActorLocation().X, MoveTargetLocation.Y - GetActorLocation().Y, 0);
	if (MoveDirction.Length() < AcceptanceDistance)
	{
		bMoving = false;
		return;
	}

	MoveDirction.Normalize(1);

	FRotator DisiredRotator = UKismetMathLibrary::MakeRotFromX(MoveDirction);
	DisiredRotator.Pitch = 0;
	DisiredRotator.Roll = 0;

	FRotator newRotator = FMath::RInterpTo(GetActorRotation(), DisiredRotator, GetWorld()->GetDeltaSeconds(), CharacterTurnSpeed);
	SetActorRotation(newRotator);
}


// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OrientPawnToMoveDirection();
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

void ABasePawn::SelectActor_Implementation(const bool Select)
{
	IndicateStaticMeshComponent->SetHiddenInGame(!Select);
}

void ABasePawn::MoveToLocation_Implementation(const FVector TargetLocation)
{
	bMoving = true;
	MoveTargetLocation = TargetLocation;

	AAIController* pawnAIController = Cast<AAIController>(GetController());
	pawnAIController->MoveToLocation(TargetLocation, AcceptanceDistance);
}

