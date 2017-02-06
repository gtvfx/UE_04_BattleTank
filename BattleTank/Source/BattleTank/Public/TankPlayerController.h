// Copyright Gavyn Thompson 2017

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Helps the palyer aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:

    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000;

    virtual void BeginPlay() override;


    virtual void Tick(float DeltaTime) override;

    // Start the tank moving the barrel with the crosshair
    void AimTowardsCrosshair();

    bool GetSightRayHitLocation(FVector& HitLocation) const;

    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
