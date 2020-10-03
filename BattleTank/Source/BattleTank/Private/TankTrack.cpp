// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Suspension.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<AActor*> UTankTrack::GetWheels() const
{
	TArray<AActor*> Suspensions;
	GetOwner()->GetAttachedActors(Suspensions);
	return Suspensions;
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	if (Wheels.Num() == 0) { return; }
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (auto Wheel : Wheels)
	{
		Cast<ASuspension>(Wheel)->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}
