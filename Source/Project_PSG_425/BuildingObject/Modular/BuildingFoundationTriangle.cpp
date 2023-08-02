#include "BuildingFoundationTriangle.h"
#include "Global.h"

ABuildingFoundationTriangle::ABuildingFoundationTriangle()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &FoundationSocket, "FoundationSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationSocket1, "FoundationSocket1", FoundationSocket);
	CHelpers::CreateSceneComponent(this, &FoundationSocket2, "FoundationSocket2", FoundationSocket);
	CHelpers::CreateSceneComponent(this, &FoundationSocket3, "FoundationSocket3", FoundationSocket);

	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket, "FoundationTriangleSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket1, "FoundationTriangleSocket1", FoundationTriangleSocket);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket2, "FoundationTriangleSocket2", FoundationTriangleSocket);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket3, "FoundationTriangleSocket3", FoundationTriangleSocket);

	CHelpers::CreateSceneComponent(this, &WallSocket, "WallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSocket);

	CHelpers::CreateSceneComponent(this, &RampSocket, "RampSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RampSocket1, "RampSocket1", RampSocket);
	CHelpers::CreateSceneComponent(this, &RampSocket2, "RampSocket2", RampSocket);
	CHelpers::CreateSceneComponent(this, &RampSocket3, "RampSocket3", RampSocket);

	// Foundation Set Location & Rotation
	FoundationSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	FoundationSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	FoundationSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	FoundationSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	FoundationSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// TriangleFoundation Set Location & Rotation
	FoundationTriangleSocket1->SetRelativeLocation(FVector(149.98f, -86.59f, 0.f));
	FoundationTriangleSocket1->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	FoundationTriangleSocket2->SetRelativeLocation(FVector(-149.98f, -86.59f, 0.f));
	FoundationTriangleSocket2->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	FoundationTriangleSocket3->SetRelativeLocation(FVector(0.f, 173.2f, 0.f));
	FoundationTriangleSocket3->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Wall Set Location & Rotation
	WallSocket1->SetRelativeLocation(FVector(75.f, -43.3f, 235.f));
	WallSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	WallSocket2->SetRelativeLocation(FVector(-75.f, -43.3f, 235.f));
	WallSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	WallSocket3->SetRelativeLocation(FVector(0.f, 86.6f, 235.f));

	// Ramp Set Location & Rotation
	RampSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	RampSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	RampSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	RampSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	RampSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// Set EBuildType
	BuildType = FoundationTriangle;
}