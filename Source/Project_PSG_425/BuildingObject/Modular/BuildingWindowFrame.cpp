#include "BuildingWindowFrame.h"
#include "Global.h"

ABuildingWindowFrame::ABuildingWindowFrame()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &WindowSocket, "WindowSocket", BuildComponents);

	// Set Mesh
	CHelpers::GetAsset(&MeshWood, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Wood/SM_Stylized_Wood_Windowframe.SM_Stylized_Wood_Windowframe'");
	CHelpers::GetAsset(&MeshStone, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Stone/SM_Stylized_Stone_Windowframe.SM_Stylized_Stone_Windowframe'");
	CHelpers::GetAsset(&MeshMetal, "StaticMesh'/Game/BuildingObject/Structures/Meshes/Stylized/Metal/SM_Stylized_Metal_Windowframe.SM_Stylized_Metal_Windowframe'");
	Mesh->SetStaticMesh(MeshWood);
}
