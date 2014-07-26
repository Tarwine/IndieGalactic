// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RoverGame.h"
#include "RoverGameHUD.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

ARoverGameHUD::ARoverGameHUD(const class FPostConstructInitializeProperties& PCIP) 
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void ARoverGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// Calculate ratio from 720p
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;

	// Get VehicleMovement component
	AWheeledVehicle* Vehicle = Cast<AWheeledVehicle>( GetOwningPawn() );
	if(Vehicle != NULL && Vehicle->VehicleMovement != NULL)
	{
		// Print vehicle speed

		float KPH = FMath::Abs(Vehicle->VehicleMovement->GetForwardSpeed()) * 0.036f;
		int32 KPH_int = FMath::FloorToInt(KPH);

		// Using FText because this is display text that should be localizable
		FText SpeedText = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));

		FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);

		FCanvasTextItem SpeedTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 455), SpeedText, HUDFont, FLinearColor::White);
		SpeedTextItem.Scale = ScaleVec;
		Canvas->DrawItem(SpeedTextItem);

		// Print vehicle gear

		int32 Gear = Vehicle->VehicleMovement->GetCurrentGear();

		// Is the Current Gear above 0?
		if (Gear > -1)
		{
			// If True display Current Gear

			// Does the Current Gear = 0 ? If False use Option 0, if True use option 1.
			FText GearName = (Gear == 0) ? LOCTEXT("N", "N") : FText::AsNumber(Gear);
			FText GearText = FText::Format(LOCTEXT("GearFormat", "Gear: {0}"), GearName);

			FCanvasTextItem GearTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f), GearText, HUDFont, FLinearColor::White);
			GearTextItem.Scale = ScaleVec;
			Canvas->DrawItem(GearTextItem);
		}
		else
		{
			// If False display R for Reverse

			FCanvasTextItem GearTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f), LOCTEXT("GearR", "Gear: R"), HUDFont, FLinearColor::Red);
			GearTextItem.Scale = ScaleVec;
			Canvas->DrawItem(GearTextItem);
		}
	}
}

#undef LOCTEXT_NAMESPACE