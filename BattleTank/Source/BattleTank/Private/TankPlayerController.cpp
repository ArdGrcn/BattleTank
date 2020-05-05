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

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		// TODO tell the controlled tank to aim at HitLocation
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	bool bHit = true;
	// Find the crosshair position
	CrosshairScreenLocation();
	// "De-project" screen position of the crosshair to a world position
	// Line-trace along that look direction, if we hit something bHit true
	// if bHit is true
		// get hit location
	return bHit;
}

FVector2D ATankPlayerController::CrosshairScreenLocation() const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	return FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
}