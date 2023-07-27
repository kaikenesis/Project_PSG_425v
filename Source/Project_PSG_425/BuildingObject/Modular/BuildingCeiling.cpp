#include "BuildingCeiling.h"
#include "Global.h"

ABuildingCeiling::ABuildingCeiling()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &CeilingSocket, "CeilingSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket4, "CeilingSocket4", CeilingSocket);

	CHelpers::CreateSceneComponent(this, &TriangleCeilingSocket, "TriangleCeilingSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &TriangleCeilingSocket1, "TriangleCeilingSocket1", TriangleCeilingSocket);
	CHelpers::CreateSceneComponent(this, &TriangleCeilingSocket2, "TriangleCeilingSocket2", TriangleCeilingSocket);
	CHelpers::CreateSceneComponent(this, &TriangleCeilingSocket3, "TriangleCeilingSocket3", TriangleCeilingSocket);
	CHelpers::CreateSceneComponent(this, &TriangleCeilingSocket4, "TriangleCeilingSocket4", TriangleCeilingSocket);

	CHelpers::CreateSceneComponent(this, &WallSocket, "WallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket5, "WallSocket5", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket6, "WallSocket6", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket7, "WallSocket7", WallSocket);
	CHelpers::CreateSceneComponent(this, &WallSocket8, "WallSocket8", WallSocket);

	CHelpers::CreateSceneComponent(this, &StairsSocket, "StairsSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);

	// Ceiling Set Location
	CeilingSocket1->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	CeilingSocket2->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	CeilingSocket3->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, -300.f, 0.f));

	// TriangleCeiling Set Location & Rotation
	TriangleCeilingSocket1->SetRelativeLocation(FVector(236.6f, 0.f, 0.f));
	TriangleCeilingSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	TriangleCeilingSocket2->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));
	TriangleCeilingSocket2->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	TriangleCeilingSocket3->SetRelativeLocation(FVector(-236.6f, 0.f, 0.f));
	TriangleCeilingSocket3->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	TriangleCeilingSocket4->SetRelativeLocation(FVector(0.f, -236.6f, 0.f));

	// Wall Set Location & Rotation
	WallSocket1->SetRelativeLocation(FVector(150.f, 0.f, 150.f));
	WallSocket1->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	WallSocket2->SetRelativeLocation(FVector(0.f, 150.f, 150.f));

	WallSocket3->SetRelativeLocation(FVector(-150.f, 0.f, 150.f));
	WallSocket3->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	WallSocket4->SetRelativeLocation(FVector(0.f, -150.f, 150.f));
	WallSocket4->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	WallSocket5->SetRelativeLocation(FVector(150.f, 0.f, -150.f));
	WallSocket5->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	WallSocket6->SetRelativeLocation(FVector(0.f, 150.f, -150.f));

	WallSocket7->SetRelativeLocation(FVector(-150.f, 0.f, -150.f));
	WallSocket7->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	WallSocket8->SetRelativeLocation(FVector(0.f, -150.f, -150.f));
	WallSocket8->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	// Stairs, Roof Set Location
	StairsSocket->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	RoofSocket->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
}
