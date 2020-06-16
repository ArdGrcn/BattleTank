// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}


void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("You died!"));
}


void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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