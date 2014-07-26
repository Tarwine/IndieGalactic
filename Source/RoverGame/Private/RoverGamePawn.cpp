// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RoverGame.h"
#include "RoverGamePawn.h"
#include "RoverGameWheelFront.h"
#include "RoverGameWheelRear.h"

ARoverGamePawn::ARoverGamePawn(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Car mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Meshes/Rover_001.Rover_001"));
	Mesh->SetSkeletalMesh(CarMesh.Object);

	static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/Sedan/Sedan_AnimBP"));
	Mesh->SetAnimInstanceClass(AnimBPClass.Class);

	// Simulation
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(VehicleMovement);

	check(Vehicle4W->WheelSetups.Num() == 4);

	Vehicle4W->WheelSetups[0].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("B_L_Tire_Front");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("B_L_Tire_Mid");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("B_L_Tire_Rear");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[0].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("B_R_Tire_Front");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("B_R_Tire_Mid");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = URoverGameWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("B_R_Tire_Rear");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	// Create a spring arm component
	SpringArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUseControllerViewRotation = false;
	Camera->FieldOfView = 90.f;

	Camera->AddLocalRotation(FRotator(0.f, 0.f, 0.0f));
}

void ARoverGamePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ARoverGamePawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARoverGamePawn::MoveRight);

	InputComponent->BindAxis("CameraX", this, &ARoverGamePawn::RotateCameraX);

	InputComponent->BindAction("Handbrake", IE_Pressed, this, &ARoverGamePawn::OnHandbrakePressed);
	InputComponent->BindAction("Handbrake", IE_Released, this, &ARoverGamePawn::OnHandbrakeReleased);
}

void ARoverGamePawn::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void ARoverGamePawn::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void ARoverGamePawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void ARoverGamePawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ARoverGamePawn::RotateCameraX(float Val){
	if (Val != 0.0f){
		Camera->AddLocalRotation(FRotator(0.f, (Val * 2.0), 0.0f));
	}
}
