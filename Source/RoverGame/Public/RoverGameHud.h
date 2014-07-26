// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "RoverGameHUD.generated.h"

UCLASS(config = Game)
class ARoverGameHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface



};
