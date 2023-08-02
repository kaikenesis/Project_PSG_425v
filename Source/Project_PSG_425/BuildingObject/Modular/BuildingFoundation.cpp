#include "BuildingFoundation.h"
#include "Global.h"

ABuildingFoundation::ABuildingFoundation()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &FoundationSocket, "FoundationSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationSocket1, "FoundationSocket1", FoundationSocket);
	CHelpers::CreateSceneComponent(this, &FoundationSocket2, "FoundationSocket2", FoundationSocket);
	CHelpers::CreateSceneComponent(this, &FoundationSocket3, "FoundationSocket3", FoundationSocket);
	CHelpers::CreateSceneComponent(this, &FoundationSocket4, "FoundationSocket4", FoundationSocket);

	CHelpers::CreateSceneComponent(this, &TriangleFoundationSocket, "TriangleFoundationSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &TriangleFoundationSocket1, "TriangleFoundationSocket1", TriangleFoundationSocket);
	CHelpers::CreateSceneComponent(this, &TriangleFoundationSocket2, "TriangleFoundationSocket2", TriangleFoundationSocket);
	CHelpers::CreateSceneComponent(this, &TriangleFoundationSocket3, "TriangleFoundationSocket3", TriangleFoundationSocket);
	CHelpers::CreateSceneComponent(this, &TriangleFoundationSocket4, "TriangleFoundationSocket4", TriangleFoundationSocket);

	CHelpers::CreateSceneComponent(this, &WallSocket, "WallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSocket);

	CHelpers::CreateSceneComponent(this, &RampSocket, "RampSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RampSocket1, "RampSocket1", RampSocket);
	CHelpers::CreateSceneComponent(this, &RampSocket2, "RampSocket2", RampSocket);
	CHelpers::CreateSceneComponent(this, &RampSocket3, "RampSocket3", RampSocket);
	CHelpers::CreateSceneComponent(this, &RampSocket4, "RampSocket4", RampSocket);

	CHelpers::CreateSceneComponent(this, &StairsSocket, "StairsSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);

	// Foundation Set Location
	FoundationSocket1->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	FoundationSocket2->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	FoundationSocket3->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	FoundationSocket4->SetRelativeLocation(FVector(0.f, -300.f, 0.f));

	// TriangleFoundation Set Location & Rotation
	TriangleFoundationSocket1->SetRelativeLocation(FVector(236.6f, 0.f, 0.f));
	TriangleFoundationSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	TriangleFoundationSocket2->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));
	TriangleFoundationSocket2->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	TriangleFoundationSocket3->SetRelativeLocation(FVector(-236.6f, 0.f, 0.f));
	TriangleFoundationSocket3->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	TriangleFoundationSocket4->SetRelativeLocation(FVector(0.f, -236.6f, 0.f));

	// Wall Set Location & Rotation
	WallSocket1->SetRelativeLocation(FVector(150.f, 0.f, 235.f));
	WallSocket1->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	WallSocket2->SetRelativeLocation(FVector(0.f, 150.f, 235.f));

	WallSocket3->SetRelativeLocation(FVector(-150.f, 0.f, 235.f));
	WallSocket3->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	WallSocket4->SetRelativeLocation(FVector(0.f, -150.f, 235.f));
	WallSocket4->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
	
	// Ramp Set Location & Rotation
	RampSocket1->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	RampSocket1->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	RampSocket2->SetRelativeLocation(FVector(0.f, 300.f, 0.f));

	RampSocket3->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	RampSocket3->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	RampSocket4->SetRelativeLocation(FVector(0.f, -300.f, 0.f));
	RampSocket4->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	// Stairs, Roof Set Location
	StairsSocket->SetRelativeLocation(FVector(0.f, 0.f, 245.f));
	RoofSocket->SetRelativeLocation(FVector(0.f, 0.f, 235.f));

	// Set EBuildType
	BuildType = Foundation;
}