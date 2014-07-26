// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RoverGame.h"
#include "RoverGameGameMode.h"
#include "RoverGamePawn.h"
#include "RoverGameHUD.h"

ARoverGameGameMode::ARoverGameGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultPawnClass = ARoverGamePawn::StaticClass();
	HUDClass = ARoverGameHUD::StaticClass();
}
