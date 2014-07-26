// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RoverGame.h"
#include "RoverGameWheelRear.h"

URoverGameWheelRear::URoverGameWheelRear(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	ShapeRadius = 16.f;
	ShapeWidth = 20.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 0.f;
}
