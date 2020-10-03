// Fill out your copyright notice in the Description page of Project Settings.


#include "Suspension.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASuspension::ASuspension()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension"));
	SetRootComponent(Suspension);

	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(Suspension);

	AxelWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxelWheelConstraint"));
	AxelWheelConstraint->SetupAttachment(Axel);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);
}

// Called when the game starts or when spawned
void ASuspension::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

// Called every frame
void ASuspension::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASuspension::SetupConstraint()
{
	// Suspension between the tank and the axel
	if (!GetAttachParentActor()) { return; }
	auto TankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	auto PrimAxel = Cast<UPrimitiveComponent>(Axel);
	if (!(PrimAxel && TankRoot)) { return; }
	Suspension->SetConstrainedComponents(TankRoot, NAME_None, PrimAxel, NAME_None);
	// Rotation constraint for the wheel
	auto PrimWheel = Cast<UPrimitiveComponent>(Wheel);
	AxelWheelConstraint->SetConstrainedComponents(PrimAxel, NAME_None, PrimWheel, NAME_None);
}

