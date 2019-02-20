// Fill out your copyright notice in the Description page of Project Settings.

#include "CSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACSCharacter::ACSCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);


}

// Called when the game starts or when spawned
void ACSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ACSCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ACSCharacter::BeginCrouch()
{
	Crouch();
}

void ACSCharacter::EndCrouch()
{
	UnCrouch();
}

void ACSCharacter::Fire()
{
	//Implement a call to fire the current weapon.
}


// Called to bind functionality to input
void ACSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Mapping
	PlayerInputComponent->BindAxis("MoveForward", this, &ACSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACSCharacter::AddControllerYawInput);


	//General Action Mapping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACSCharacter::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACSCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACSCharacter::EndCrouch);

	//Custom Action Mapping
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACSCharacter::Fire);

}

