#include "BaseBuildingObject.h"
#include "Global.h"

ABaseBuildingObject::ABaseBuildingObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Root);

	CHelpers::GetAsset(&CanBuildMaterialInterface, "MaterialInstanceConstant'/Game/Materials/Instance/Dummy/MI_Can_Build.MI_Can_Build'");
	CHelpers::GetAsset(&CanNotBuildMaterialInterface, "MaterialInstanceConstant'/Game/Materials/Instance/Dummy/MI_CanNot_Build.MI_CanNot_Build'");

}

void ABaseBuildingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBuildingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuildingObject::SetMaterialCanBuild()
{
	Mesh->SetMaterial(0, CanBuildMaterialInterface);
}

void ABaseBuildingObject::SetMaterialCanNotBuild()
{
	Mesh->SetMaterial(0, CanNotBuildMaterialInterface);
}

