#include "BuildingWall.h"
#include "Global.h"

ABuildingWall::ABuildingWall()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &CeilingSocket, "CeilingSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket4, "CeilingSocket4", CeilingSocket);

	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket, "CeilingTriangleSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket1, "CeilingTriangleSocket1", CeilingTriangleSocket);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket2, "CeilingTriangleSocket2", CeilingTriangleSocket);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket3, "CeilingTriangleSocket3", CeilingTriangleSocket);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket4, "CeilingTriangleSocket4", CeilingTriangleSocket);

	CHelpers::CreateSceneComponent(this, &WallSocket, "WallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSocket);

	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket1, "RoofSocket1", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket2, "RoofSocket2", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket3, "RoofSocket3", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket4, "RoofSocket4", RoofSocket);

	// Ceiling Set Location
	CeilingSocket1->SetRelativeLocation(FVector(0.f, -150.f, 150.f));
	CeilingSocket2->SetRelativeLocation(FVector(0.f, 150.f, 150.f));
	CeilingSocket3->SetRelativeLocation(FVector(0.f, -150.f, -150.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, 150.f, -150.f));

	// TriangleCeiling Set Location & Rotation
	CeilingTriangleSocket1->SetRelativeLocation(FVector(0.f, -86.6f, 150.f));

	CeilingTriangleSocket2->SetRelativeLocation(FVector(0.f, 86.6f, 150.f));
	CeilingTriangleSocket2->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	CeilingTriangleSocket3->SetRelativeLocation(FVector(0.f, -86.6f, -150.f));

	CeilingTriangleSocket4->SetRelativeLocation(FVector(0.f, 86.6f, -150.f));
	CeilingTriangleSocket4->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Wall Set Location
	WallSocket1->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
	WallSocket2->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	WallSocket3->SetRelativeLocation(FVector(0.f, 0.f, -300.f));
	WallSocket4->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));

	// Roof Set Location & Rotation
	RoofSocket1->SetRelativeLocation(FVector(0.f, -150.f, 300.f));
	RoofSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	RoofSocket2->SetRelativeLocation(FVector(0.f, 150.f, 300.f));
	RoofSocket2->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	RoofSocket3->SetRelativeLocation(FVector(0.f, -150.f, 0.f));
	RoofSocket3->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	RoofSocket4->SetRelativeLocation(FVector(0.f, 150.f, 0.f));
	RoofSocket4->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Set EBuildType
	BuildType = Wall;
}