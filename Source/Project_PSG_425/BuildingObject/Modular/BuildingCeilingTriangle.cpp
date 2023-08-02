#include "BuildingCeilingTriangle.h"
#include "Global.h"

ABuildingCeilingTriangle::ABuildingCeilingTriangle()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &CeilingSocket, "CeilingSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSocket);

	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket, "CeilingTriangleSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket1, "CeilingTriangleSocket1", CeilingTriangleSocket);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket2, "CeilingTriangleSocket2", CeilingTriangleSocket);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket3, "CeilingTriangleSocket3", CeilingTriangleSocket);

	CHelpers::CreateSceneComponent(this, &WallSocket, "WallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket5, "WallSocket5", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket6, "WallSocket6", WallSocket);

	// Ceiling Set Location
	CeilingSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	CeilingSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	CeilingSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	CeilingSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	CeilingSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// TriangleCeiling Set Location & Rotation
	CeilingTriangleSocket1->SetRelativeLocation(FVector(149.98f, -86.59f, 0.f));
	CeilingTriangleSocket1->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	CeilingTriangleSocket2->SetRelativeLocation(FVector(-149.98f, -86.59f, 0.f));
	CeilingTriangleSocket2->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	CeilingTriangleSocket3->SetRelativeLocation(FVector(0.f, 173.2f, 0.f));
	CeilingTriangleSocket3->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Wall Set Location & Rotation
	WallSocket1->SetRelativeLocation(FVector(75.f, -43.3f, 150.f));
	WallSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	WallSocket2->SetRelativeLocation(FVector(-75.f, -43.3f, 150.f));
	WallSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	WallSocket3->SetRelativeLocation(FVector(0.f, 86.6f, 150.f));

	WallSocket4->SetRelativeLocation(FVector(75.f, -43.3f, -150.f));
	WallSocket4->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	WallSocket5->SetRelativeLocation(FVector(-75.f, -43.3f, -150.f));
	WallSocket5->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	WallSocket6->SetRelativeLocation(FVector(0.f, 86.6f, -150.f));

	// Set EBuildType
	BuildType = CeilingTriangle;
}