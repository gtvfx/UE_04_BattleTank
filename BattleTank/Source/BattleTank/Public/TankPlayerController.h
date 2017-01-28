// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0;

    virtual void BeginPlay() override;

    ATank* GetControlledTank() const;

    virtual void Tick(float DeltaTime) override;

    // Start the tank moving the barrel with the crosshair
    void AimTowardsCrosshair();

    bool GetSightRayHitLocation(FVector& HitLocation) const;

    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
