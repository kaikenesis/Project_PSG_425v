#include "BuildingRoof.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingRoof::ABuildingRoof()
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

	CHelpers::CreateSceneComponent(this, &RoofSockets, "RoofSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket1, "RoofSocket1", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket2, "RoofSocket2", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket3, "RoofSocket3", RoofSockets);
	CHelpers::CreateSceneComponent(this, &RoofSocket4, "RoofSocket4", RoofSockets);

	CHelpers::CreateSceneComponent(this, &RoofWallSockets, "RoofWallSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofWallSocketLeft, "RoofWallSocketLeft", RoofWallSockets);
	CHelpers::CreateSceneComponent(this, &RoofWallSocketRight, "RoofWallSocketRight", RoofWallSockets);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(180.f, 135.f, 10.f));
	BuildCollision1->SetRelativeRotation(FRotator(137.f, 0.f, 0.f));

	// Set Ceiling Location
	CeilingSocket1->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	CeilingSocket2->SetRelativeLocation(FVector(-300.f, 0.f, 150.f));
	CeilingSocket3->SetRelativeLocation(FVector(300.f, 0.f, -150.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, 0.f, -150.f));

	// Set Roof Location
	RoofSocket1->SetRelativeLocation(FVector(300.f, 0.f, -300.f));
	RoofSocket2->SetRelativeLocation(FVector(0.f, -300.f, 0.f));
	RoofSocket3->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	RoofSocket4->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));

	// Set RoofWall Location
	RoofWallSocketLeft->SetRelativeLocation(FVector(0.f, -150.f, 0.f));
	RoofWallSocketRight->SetRelativeLocation(FVector(0.f, 150.f, 0.f));

	// Set Mesh
	CHelpers::GetAsset(&MeshWood, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Wood/SM_Stylized_Wood_Roof.SM_Stylized_Wood_Roof'");
	CHelpers::GetAsset(&MeshStone, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Stone/SM_Stylized_Stone_Roof.SM_Stylized_Stone_Roof'");
	CHelpers::GetAsset(&MeshMetal, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Metal/SM_Stylized_Metal_Roof.SM_Stylized_Metal_Roof'");
	Mesh->SetStaticMesh(MeshWood);

	// Set EBuildType
	BuildType = EBuildType::Roof;
}