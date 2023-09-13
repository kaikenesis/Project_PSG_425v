#include "BuildingFoundation.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingFoundation::ABuildingFoundation()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &BuildCollisions, "BuildCollisions", BuildComponents);
	CHelpers::CreateSceneComponent(this, &BuildCollision1, "BuildCollision1", BuildCollisions);

	CHelpers::CreateSceneComponent(this, &FoundationSockets, "FoundationSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationSocket1, "FoundationSocket1", FoundationSockets);
	CHelpers::CreateSceneComponent(this, &FoundationSocket2, "FoundationSocket2", FoundationSockets);
	CHelpers::CreateSceneComponent(this, &FoundationSocket3, "FoundationSocket3", FoundationSockets);
	CHelpers::CreateSceneComponent(this, &FoundationSocket4, "FoundationSocket4", FoundationSockets);

	CHelpers::CreateSceneComponent(this, &FoundationTriangleSockets, "FoundationTriangleSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket1, "FoundationTriangleSocket1", FoundationTriangleSockets);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket2, "FoundationTriangleSocket2", FoundationTriangleSockets);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket3, "FoundationTriangleSocket3", FoundationTriangleSockets);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket4, "FoundationTriangleSocket4", FoundationTriangleSockets);

	CHelpers::CreateSceneComponent(this, &WallSockets, "WallSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket4, "WallSocket4", WallSockets);

	CHelpers::CreateSceneComponent(this, &RampSockets, "RampSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RampSocket1, "RampSocket1", RampSockets);
	CHelpers::CreateSceneComponent(this, &RampSocket2, "RampSocket2", RampSockets);
	CHelpers::CreateSceneComponent(this, &RampSocket3, "RampSocket3", RampSockets);
	CHelpers::CreateSceneComponent(this, &RampSocket4, "RampSocket4", RampSockets);

	CHelpers::CreateSceneComponent(this, &StairsSocket, "StairsSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(149.f, 149.f, 84.f));

	// Foundation Set Location
	FoundationSocket1->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
	FoundationSocket2->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	FoundationSocket3->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	FoundationSocket4->SetRelativeLocation(FVector(0.f, -300.f, 0.f));

	// FoundationTriangle Set Location & Rotation
	FoundationTriangleSocket1->SetRelativeLocation(FVector(236.6f, 0.f, 0.f));
	FoundationTriangleSocket1->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	FoundationTriangleSocket2->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));
	FoundationTriangleSocket2->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));

	FoundationTriangleSocket3->SetRelativeLocation(FVector(-236.6f, 0.f, 0.f));
	FoundationTriangleSocket3->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	FoundationTriangleSocket4->SetRelativeLocation(FVector(0.f, -236.6f, 0.f));

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

	// Set Mesh
	CHelpers::GetAsset(&MeshWood, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Wood/SM_Stylized_Wood_Foundation.SM_Stylized_Wood_Foundation'");
	CHelpers::GetAsset(&MeshStone, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Stone/SM_Stylized_Stone_Foundation.SM_Stylized_Stone_Foundation'");
	CHelpers::GetAsset(&MeshMetal, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Metal/SM_Stylized_Metal_Foundation.SM_Stylized_Metal_Foundation'");
	Mesh->SetStaticMesh(MeshWood);

	// Set EBuildType
	BuildType = EBuildType::Foundation;
}
