// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BasePawn.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	}

	//Add Mapping Context
	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (System)
	{
		System->AddMappingContext(DefaultInputMappingContext, 0);
		UE_LOG(LogTemp,Display,TEXT("Mapping context added!"));
	}

	//Bind Select Action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::Select);

		EnhancedInputComponent->BindAction(CommandInputAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::CommandSelectActor);
	}
}

void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	FHitResult HitResult;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	//deselect previous selected actor
	if (SelectPawn != nullptr)
	{
		if (SelectPawn->GetClass()->ImplementsInterface(USelectInterface::StaticClass()))
		{
			ISelectInterface::Execute_SelectActor(SelectPawn, false);
		}
	}

	SelectPawn = HitResult.GetActor();

	if (SelectPawn != nullptr)
	{
		if (SelectPawn->GetClass()->ImplementsInterface(USelectInterface::StaticClass()))
		{
			ISelectInterface::Execute_SelectActor(SelectPawn, true);
		}
	}
}

void ATopDownPlayerController::CommandSelectActor(const FInputActionValue& Value)
{
	if (SelectPawn != nullptr)
	{
		if (SelectPawn->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
		{
			FHitResult HitResult;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

			if (HitResult.bBlockingHit)
			{
				INavigableInterface::Execute_MoveToLocation(SelectPawn, HitResult.Location);
			}
		}
	}
}
