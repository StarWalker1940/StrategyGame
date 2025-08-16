// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BasePawn.h"
#include "SelectHUD.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SelectHUD = Cast<ASelectHUD>(GetHUD());
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
	
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Started, this, &ATopDownPlayerController::SelectBegin);
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::SelectOnGoing);
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::SelectEnd);
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

void ATopDownPlayerController::SelectBegin(const FInputActionValue& Value)
{
	GetMousePosition(SelectBeginLoc.X, SelectBeginLoc.Y);
}

void ATopDownPlayerController::SelectOnGoing(const FInputActionValue& Value)
{
	FVector2D CurrentLoc;
	GetMousePosition(CurrentLoc.X, CurrentLoc.Y);

	FVector2D DeltaArea;
	DeltaArea.X = CurrentLoc.X - SelectBeginLoc.X;
	DeltaArea.Y = CurrentLoc.Y - SelectBeginLoc.Y;

	if (SelectHUD)
	{
		SelectHUD->SetShowDrawArea(SelectBeginLoc, DeltaArea);
	}
}

void ATopDownPlayerController::SelectEnd(const FInputActionValue& Value)
{
	FVector2D EndLoc;
	GetMousePosition(EndLoc.X, EndLoc.Y);
	
	if (SelectHUD)
	{
		SelectHUD->SetHideDrawArea();
		FTimerHandle TH_SelectMutiActors;
		GetWorld()->GetTimerManager().SetTimer(TH_SelectMutiActors, this, &ATopDownPlayerController::SelectMutiActors, 0.05f, false);
	}
}

void ATopDownPlayerController::SelectMutiActors()
{
	if (SelectHUD)
	{
		//Deselect SelectActors
		for (AActor* SomeActor : SelectActors)
		{
			if (SomeActor != nullptr)
			{
				if (SomeActor->GetClass()->ImplementsInterface(USelectInterface::StaticClass()))
				{
					ISelectInterface::Execute_SelectActor(SomeActor, false);
				}
			}
		}

		SelectActors = SelectHUD->GetSelctActors();

		//Show SelectActors
		for (AActor* SomeActor : SelectActors)
		{
			if (SomeActor != nullptr)
			{
				if (SomeActor->GetClass()->ImplementsInterface(USelectInterface::StaticClass()))
				{
					ISelectInterface::Execute_SelectActor(SomeActor, true);
				}
			}
		}
	}
}
