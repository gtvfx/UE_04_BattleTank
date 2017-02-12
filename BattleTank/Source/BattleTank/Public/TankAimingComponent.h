// Copyright Gavyn Thompson 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
     void Init(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

protected:

    UPROPERTY(BlueprintReadonly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
	
private:

    // Sets default values for this component's properties
    UTankAimingComponent();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFuncion) override;

    bool IsBarrelMoving();

    void MoveBarrelTowards(FVector AimDirection);

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ReloadTimeInSeconds = 3;

    double LastFireTime = 0;

    FVector AimDirection;
};
