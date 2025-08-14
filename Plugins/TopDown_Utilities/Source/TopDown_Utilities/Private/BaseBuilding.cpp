// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include <Components/BoxComponent.h>

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

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuilding::SelectActor_Implementation(const bool select)
{
	IndicateStaticMeshComponent->SetHiddenInGame(!select);
}

