// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerControlledTank = GetPlayerControlledTank();
	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player controlled tank not found."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controls %s."), *PlayerControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPlayerControlledTank()) { return; }

	// get world location if you linetrace through crosshair
	// if it hits the landscape
		// tell the controlled tank to aim at this point
}