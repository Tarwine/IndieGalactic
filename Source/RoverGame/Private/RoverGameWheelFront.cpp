// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RoverGame.h"
#include "RoverGameWheelFront.h"

URoverGameWheelFront::URoverGameWheelFront(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	ShapeRadius = 16.f;
	ShapeWidth = 20.0f;
	bAffectedByHandbrake = false;
	SteerAngle = 50.f;
}
