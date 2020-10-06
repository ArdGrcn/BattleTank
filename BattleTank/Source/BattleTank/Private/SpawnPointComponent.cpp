// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Suspension.h"
#include "TankTrack.h"

// Sets default values for this component's properties
USpawnPointComponent::USpawnPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();
	
	auto Transform = GetComponentTransform();	

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, Transform);

	if (SpawnedActor)
	{
		SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	}

	UGameplayStatics::FinishSpawningActor(SpawnedActor, Transform);
}

// Called every frame
void USpawnPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* USpawnPointComponent::GetSpawnedActor() const
{
	return SpawnedActor;
}
