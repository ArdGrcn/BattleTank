// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.generated.h" // Must be the last include


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

	void AimTowardsCrosshair() const;

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	FVector2D CrosshairScreenLocation() const;

	bool GetLookDirection(FVector2D CrosshairScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	// Member variables
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.0;
};
