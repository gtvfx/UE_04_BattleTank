// Copyright Gavyn Thompson 2017

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

    virtual void BeginPlay() override;

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Fire();

protected:
    UPROPERTY(BluePrintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;
    
    UPROPERTY(BluePrintReadOnly)
    UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();
	
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ReloadTimeInSeconds = 3;

    double LastFireTime = 0;

    UTankBarrel* Barrel = nullptr; // TODO remove
};
