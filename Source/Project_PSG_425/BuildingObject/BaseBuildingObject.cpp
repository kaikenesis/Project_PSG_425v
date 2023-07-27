#include "BaseBuildingObject.h"
#include "Global.h"

ABaseBuildingObject::ABaseBuildingObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Root);

}

void ABaseBuildingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBuildingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

