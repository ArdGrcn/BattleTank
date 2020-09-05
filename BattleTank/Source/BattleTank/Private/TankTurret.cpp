// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// move the turret the right amount this frame
	// given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}