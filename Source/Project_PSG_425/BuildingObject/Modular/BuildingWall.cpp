#include "BuildingWall.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingWall::ABuildingWall()
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

	CHelpers::CreateSceneComponent(this, &RoofSockets, "RoofSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket1, "RoofSocket1", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket2, "RoofSocket2", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket3, "RoofSocket3", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket4, "RoofSocket4", RoofSockets);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(130.f, 5.f, 130.f));

	// Set Ceiling Location
	CeilingSocket1->SetRelativeLocation(FVector(0.f, -150.f, 150.f));
	CeilingSocket2->SetRelativeLocation(FVector(0.f, 150.f, 150.f));
	CeilingSocket3->SetRelativeLocation(FVector(0.f, -150.f, -150.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, 150.f, -150.f));

	// Set CeilingTriangle Location & Rotation
	CeilingTriangleSocket1->SetRelativeLocation(FVector(0.f, -86.6f, 150.f));

	CeilingTriangleSocket2->SetRelativeLocation(FVector(0.f, 86.6f, 150.f));
	CeilingTriangleSocket2->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	CeilingTriangleSocket3->SetRelativeLocation(FVector(0.f, -86.6f, -150.f));

	CeilingTriangleSocket4->SetRelativeLocation(FVector(0.f, 86.6f, -150.f));
	CeilingTriangleSocket4->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Set Wall Location
	WallSocket1->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
	WallSocket2->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	WallSocket3->SetRelativeLocation(FVector(0.f, 0.f, -300.f));
	WallSocket4->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));

	// Set Roof Location & Rotation
	RoofSocket1->SetRelativeLocation(FVector(0.f, -150.f, 300.f));
	RoofSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	RoofSocket2->SetRelativeLocation(FVector(0.f, 150.f, 300.f));
	RoofSocket2->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	RoofSocket3->SetRelativeLocation(FVector(0.f, -150.f, 0.f));
	RoofSocket3->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	RoofSocket4->SetRelativeLocation(FVector(0.f, 150.f, 0.f));
	RoofSocket4->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Set EBuildType & Init MeshType
	BuildType = EBuildType::Wall;
}
