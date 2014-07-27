// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "RoverGamePawn.generated.h"

UCLASS(config=Game)
class ARoverGamePawn : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()

	/** Spring arm that will offset the camera */
	/*UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	TSubobjectPtr<class USpringArmComponent> SpringArm;*/

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	TSubobjectPtr<class UCameraComponent> Camera;

	UFUNCTION(BlueprintImplementableEvent)
        virtual void OnMotorMovement();

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Pawn interface

	/** Handle pressing forwards */
	void MoveForward(float Val);
	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();

	void RotateCameraX(float Val);
	void RotateCameraY(float Val);
};
