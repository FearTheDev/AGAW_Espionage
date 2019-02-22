// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSGrabber.generated.h"


class UPhysicsHandleComponent;
class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESPIONAGEGAME_API UCSGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPhysicsHandleComponent* PhysicsHandleComp = nullptr;

	void FindPhysicsHandleComponent();

	FHitResult GetFirstPhysicsBodyInReach() const;

	FTwoVectors GetLineTracePoints() const;

	float ModifiedGrabberRange;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoluted Studios Grabber")
		float GrabberReach = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoluted Studios Grabber")
		bool bGrabberModeEnabled = false;

	UFUNCTION(BlueprintCallable, Category="Grabber")
	FHitResult TryGrab();
};