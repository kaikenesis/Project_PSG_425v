#include "BuildingCeiling.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingCeiling::ABuildingCeiling()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &BuildCollisions, "BuildCollisions", BuildComponents);
	CHelpers::CreateSceneComponent(this, &BuildCollision1, "BuildCollision1", BuildCollisions);

	CHelpers::CreateSceneComponent(this, &CeilingSockets, "CeilingSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSockets);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSockets);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSockets);
	CHelpers::CreateSceneComponent(this, &CeilingSocket4, "CeilingSocket4", CeilingSockets);

	CHelpers::CreateSceneComponent(this, &CeilingTriangleSockets, "CeilingTriangleSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket1, "CeilingTriangleSocket1", CeilingTriangleSockets);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket2, "CeilingTriangleSocket2", CeilingTriangleSockets);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket3, "CeilingTriangleSocket3", CeilingTriangleSockets);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket4, "CeilingTriangleSocket4", CeilingTriangleSockets);

	CHelpers::CreateSceneComponent(this, &WallSockets, "WallSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket5, "WallSocket5", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket6, "WallSocket6", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket7, "WallSocket7", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket8, "WallSocket8", WallSockets);

	CHelpers::CreateSceneComponent(this, &StairsSocket, "StairsSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(130.f, 130.f, 10.f));
	
	// Set Ceiling Location
	CeilingSocket1->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	CeilingSocket2->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	CeilingSocket3->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, -300.f, 0.f));

	// Set CeilingTriangle Location & Rotation
	CeilingTriangleSocket1->SetRelativeLocation(FVector(236.6f, 0.f, 0.f));
	CeilingTriangleSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	CeilingTriangleSocket2->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));
	CeilingTriangleSocket2->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	CeilingTriangleSocket3->SetRelativeLocation(FVector(-236.6f, 0.f, 0.f));
	CeilingTriangleSocket3->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	CeilingTriangleSocket4->SetRelativeLocation(FVector(0.f, -236.6f, 0.f));

	// Set Wall Location & Rotation
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

	// Set Stairs, Roof Location
	StairsSocket->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	RoofSocket->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

	// Set EBuildType
	BuildType = EBuildType::Ceiling;
}
