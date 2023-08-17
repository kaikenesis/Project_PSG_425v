#include "BuildingDoorFrame.h"
#include "Global.h"

ABuildingDoorFrame::ABuildingDoorFrame()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &DoorSocket, "DoorSocket", BuildComponents);

	// Set Mesh
	CHelpers::GetAsset(&MeshWood, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Wood/SM_Stylized_Wood_Doorframe.SM_Stylized_Wood_Doorframe'");
	CHelpers::GetAsset(&MeshStone, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Stone/SM_Stylized_Stone_Doorframe.SM_Stylized_Stone_Doorframe'");
	CHelpers::GetAsset(&MeshMetal, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Metal/SM_Stylized_Metal_Doorframe.SM_Stylized_Metal_Doorframe'");
	Mesh->SetStaticMesh(MeshWood);
}