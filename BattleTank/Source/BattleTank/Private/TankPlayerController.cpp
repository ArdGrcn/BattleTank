// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPlayerControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController can't find AimingComponent at BeginPlay."));
		return;
	}

	FoundAimingComponent(AimingComponent);
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


void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!ensure(GetPlayerControlledTank())) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetPlayerControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector LookDirection;

	if (GetLookDirection(CrosshairScreenLocation(), LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}	
	}

	return false; // if set to true turret and barrel reset to default position when no solution is found
}


FVector2D ATankPlayerController::CrosshairScreenLocation() const
{
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	return FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
}


bool ATankPlayerController::GetLookDirection(FVector2D CrosshairScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(
		CrosshairScreenLocation.X,
		CrosshairScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility)
		)
	{
		HitLocation = HitResult.ImpactPoint;
		return true;
	}

	return false;
}