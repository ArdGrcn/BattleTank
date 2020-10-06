// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Suspension.h"
#include "SpawnPointComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<ASuspension*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	TArray<ASuspension*> Suspensions;
	GetChildrenComponents(false, Children);
	for (auto Child : Children)
	{
		if (USpawnPointComponent* Spawnpoint = Cast<USpawnPointComponent>(Child))
		{
			if (ASuspension* Suspension = Cast<ASuspension>(Spawnpoint->GetSpawnedActor()))
			{
				Suspensions.Add(Suspension);
			}
		}
	}
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
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}
