#include "BuildingCeilingTriangle.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingCeilingTriangle::ABuildingCeilingTriangle()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &BuildCollisions, "BuildCollisions", BuildComponents);
	CHelpers::CreateSceneComponent(this, &BuildCollision1, "BuildCollision1", BuildCollisions);
	CHelpers::CreateSceneComponent(this, &BuildCollision2, "BuildCollision2", BuildCollisions);
	CHelpers::CreateSceneComponent(this, &BuildCollision3, "BuildCollision3", BuildCollisions);
	CHelpers::CreateSceneComponent(this, &BuildCollision4, "BuildCollision4", BuildCollisions);
	CHelpers::CreateSceneComponent(this, &BuildCollision5, "BuildCollision5", BuildCollisions);
	CHelpers::CreateSceneComponent(this, &BuildCollision6, "BuildCollision6", BuildCollisions);

	CHelpers::CreateSceneComponent(this, &CeilingSockets, "CeilingSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSockets);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSockets);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSockets);

	CHelpers::CreateSceneComponent(this, &CeilingTriangleSockets, "CeilingTriangleSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket1, "CeilingTriangleSocket1", CeilingTriangleSockets);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket2, "CeilingTriangleSocket2", CeilingTriangleSockets);
	CHelpers::CreateSceneComponent(this, &CeilingTriangleSocket3, "CeilingTriangleSocket3", CeilingTriangleSockets);

	CHelpers::CreateSceneComponent(this, &WallSockets, "WallSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket5, "WallSocket5", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket6, "WallSocket6", WallSockets);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(125.f, 20.f, 10.f));
	BuildCollision1->SetRelativeLocation(FVector(0.f, 65.f, 0.f));

	BuildCollision2->SetBoxExtent(FVector(125.f, 20.f, 10.f));
	BuildCollision2->SetRelativeLocation(FVector(56.29f, -32.5f, 0.f));
	BuildCollision2->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	BuildCollision3->SetBoxExtent(FVector(125.f, 20.f, 10.f));
	BuildCollision3->SetRelativeLocation(FVector(-56.29f, -32.5f, 0.f));
	BuildCollision3->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	BuildCollision4->SetBoxExtent(FVector(80.f, 20.f, 10.f));
	BuildCollision4->SetRelativeLocation(FVector(0.f, 25.f, 0.f));

	BuildCollision5->SetBoxExtent(FVector(60.f, 20.f, 10.f));
	BuildCollision5->SetRelativeLocation(FVector(0.f, -15.f, 0.f));

	BuildCollision6->SetBoxExtent(FVector(40.f, 30.f, 10.f));
	BuildCollision6->SetRelativeLocation(FVector(0.f, -65.f, 0.f));

	// Set Ceiling Location
	CeilingSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	CeilingSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	CeilingSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	CeilingSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	CeilingSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// Set CeilingTriangle Location & Rotation
	CeilingTriangleSocket1->SetRelativeLocation(FVector(149.98f, -86.59f, 0.f));
	CeilingTriangleSocket1->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	CeilingTriangleSocket2->SetRelativeLocation(FVector(-149.98f, -86.59f, 0.f));
	CeilingTriangleSocket2->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	CeilingTriangleSocket3->SetRelativeLocation(FVector(0.f, 173.2f, 0.f));
	CeilingTriangleSocket3->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Set Wall Location & Rotation
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

	// Set Mesh
	CHelpers::GetAsset(&MeshWood, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Wood/SM_Stylized_Wood_Triangle_Ceiling.SM_Stylized_Wood_Triangle_Ceiling'");
	CHelpers::GetAsset(&MeshStone, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Stone/SM_Stylized_Stone_Tri_Ceiling.SM_Stylized_Stone_Tri_Ceiling'");
	CHelpers::GetAsset(&MeshMetal, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Metal/SM_Stylized_Metal_Tri_Ceiling.SM_Stylized_Metal_Tri_Ceiling'");
	Mesh->SetStaticMesh(MeshWood);

	// Set EBuildType
	BuildType = EBuildType::CeilingTriangle;
}