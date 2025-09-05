// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include <Components/BoxComponent.h>
#include <EnhancedInputComponent.h>
#include <InputAction.h>

// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create StaticMeshComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	//Create IndicateStaticMeshComponent
	IndicateStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IndicateStaticMesh"));
	IndicateStaticMeshComponent->SetupAttachment(RootComponent);
	IndicateStaticMeshComponent->SetHiddenInGame(true);
	IndicateStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ABaseBuilding::GetFactionID_Implementation()
{
	return FactionID;
}

void ABaseBuilding::SetFactionID_Implementation(int32 val)
{
	FactionID = val;
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuilding::SelectActor_Implementation(const bool select)
{
	IndicateStaticMeshComponent->SetHiddenInGame(!select);
}

void ABaseBuilding::EnablePlacingMode()
{
	UE_LOG(LogTemp, Display, TEXT("placeing ========== EnablePlacingMode"));
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		EnableInput(PC);
		UEnhancedInputComponent* EnhanceComp = Cast<UEnhancedInputComponent>(PC->InputComponent);
		if (EnhanceComp)
		{
			EnhanceComp->BindAction(PlaceAction, ETriggerEvent::Completed, this, &ABaseBuilding::PlaceBuilding);
		}
		GetWorld()->GetTimerManager().SetTimer(TH_CheckValidity, this, &ABaseBuilding::CheckPlacementValidity, 0.01f, true);
		this->SetActorEnableCollision(false);
	}
}

void ABaseBuilding::CheckPlacementValidity()
{
	TogglePlaceBuildingColor(bCanPlace);

	bCanPlace = false;

	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (! HitResult.bBlockingHit)
	{
		return;
	}

	SetActorLocation(HitResult.Location);

	if (! HitResult.GetActor()->ActorHasTag(CanPlaceFlag))
	{
		return;
	}
	
	TArray<FHitResult> HitArray;
	FVector HalfExtents = BoxExtents / 2;
	FVector StartLoc = HitResult.Location + FVector(0, 0, HalfExtents.Z);
	FVector EndLoc = StartLoc + FVector::UpVector;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;
	GetWorld()->SweepMultiByChannel(HitArray, StartLoc, EndLoc, GetActorRotation().Quaternion(), ECollisionChannel::ECC_Visibility, FCollisionShape::MakeBox(HalfExtents),QueryParams);

	for (const FHitResult& BoxHitResult : HitArray)
	{
		if (!(BoxHitResult.GetActor() !=nullptr && BoxHitResult.GetActor()->ActorHasTag(CanPlaceFlag)))
		{
			//DrawDebugBox(GetWorld(), StartLoc, HalfExtents, GetActorRotation().Quaternion(),FColor::Red, false, 1.f);
			return;
		}
	}


	//DrawDebugBox(GetWorld(), StartLoc, HalfExtents, GetActorRotation().Quaternion(), FColor::Green, false, 1.f);
	bCanPlace = true;
}

void ABaseBuilding::PlaceBuilding(const FInputActionValue& value)
{
	if (!bCanPlace)
	{
		SetLifeSpan(0.1);
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("placeing ========== PlaceBuilding"));
	GetWorld()->GetTimerManager().ClearTimer(TH_CheckValidity);
	this->SetActorEnableCollision(true);
}

void ABaseBuilding::CancelBuildingPlacement(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("placeing ========== CancelBuildingPlacement"));
}

