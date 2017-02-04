// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call super. We will do a complete replace of functionality
    auto TankName = GetOwner()->GetName();
    auto MoveVelocityStr = MoveVelocity.ToString();

    UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityStr);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    // TODO prevent double-speed from two control inputs
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);

    // TODO prevent double-speed from two control inputs
}