// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGrabber.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"

#define OUT

// Sets default values for this component's properties
UCSGrabber::UCSGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCSGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
}


FHitResult UCSGrabber::TryGrab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	return HitResult;
}

void UCSGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandleComp = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

FHitResult UCSGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FTwoVectors TracePoints = GetLineTracePoints();

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		TracePoints.v1,
		TracePoints.v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	return HitResult;
}

FTwoVectors UCSGrabber::GetLineTracePoints() const
{
	FVector StartLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT StartLocation, OUT PlayerViewPointRotation);
	StartLocation = GetOwner()->GetActorLocation();

	FVector EndLocation = GetOwner()->GetActorLocation() + PlayerViewPointRotation.Vector() *GrabberReach;

	return FTwoVectors(StartLocation, EndLocation);

}

// Called every frame
void UCSGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!PhysicsHandleComp)
	{
		return;
	}

	if (PhysicsHandleComp->GrabbedComponent)
	{

		PhysicsHandleComp->SetTargetLocation(GetLineTracePoints().v2);

	}
}

