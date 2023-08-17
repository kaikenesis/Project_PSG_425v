#include "BaseBuildingObject.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Modular/BuildingCeiling.h"
#include "Modular/BuildingCeilingTriangle.h"
#include "Modular/BuildingDoorFrame.h"
#include "Modular/BuildingFoundation.h"
#include "Modular/BuildingFoundationTriangle.h"
#include "Modular/BuildingRoof.h"
#include "Modular/BuildingWall.h"
#include "Modular/BuildingWindowFrame.h"

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
	
	OnActorBeginOverlap.AddDynamic(this, &ABaseBuildingObject::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ABaseBuildingObject::OnEndOverlap);
}

void ABaseBuildingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuildingObject::OnBeginOverlap(AActor* OverlapActor, AActor* OtherActor)
{
	if (IsBuilded == false)
	{
		if (Cast<ABaseBuildingObject>(OverlapActor) || Cast<ACharacter>(OverlapActor))
			OverlapActors.Add(OverlapActor);

		if (OverlapActors.Num() > 0)
			SetMaterialCanNotBuild();

		CLog::Print(OverlapActors.Num());
	}		
}

void ABaseBuildingObject::OnEndOverlap(AActor* OverlapActor, AActor* OtherActor)
{
	if (IsBuilded == false)
	{
		if (Cast<ABaseBuildingObject>(OverlapActor) || Cast<ACharacter>(OverlapActor))
			if(OverlapActors.Contains(OverlapActor))
				OverlapActors.RemoveSingle(OverlapActor);

		if (OverlapActors.Num() < 1)
			SetMaterialCanBuild();

		CLog::Print(OverlapActors.Num());
	}
}

void ABaseBuildingObject::SetMaterialCanBuild()
{
	Mesh->SetMaterial(0, CanBuildMaterialInterface);
	bCanBuild = true;
}

void ABaseBuildingObject::SetMaterialCanNotBuild()
{
	Mesh->SetMaterial(0, CanNotBuildMaterialInterface);
	bCanBuild = false;
}

void ABaseBuildingObject::SetBuildType(EBuildType Type)
{
	switch (BuildType)
	{
		case Ceiling:
		{
			ABuildingCeiling* actor = Cast<ABuildingCeiling>(this);
			Mesh = actor->Mesh;
			break;
		}
		case CeilingTriangle:
		{
			ABuildingCeilingTriangle* actor = Cast<ABuildingCeilingTriangle>(this);
			Mesh = actor->Mesh;
			break;
		}
		case Foundation:
		{
			ABuildingFoundation* actor = Cast<ABuildingFoundation>(this);
			Mesh = actor->Mesh;
			break;
		}
		case FoundationTriangle:
		{
			ABuildingFoundationTriangle* actor = Cast<ABuildingFoundationTriangle>(this);
			Mesh = actor->Mesh;
			break;
		}
		case Roof:
		{
			ABuildingRoof* actor = Cast<ABuildingRoof>(this);
			Mesh = actor->Mesh;
			break;
		}
		case RoofWall:
		{
			break;
		}
		case Wall:
		{
			ABuildingWall* actor = Cast<ABuildingWall>(this);
			Mesh = actor->Mesh;
			break;
		}
		case Ramp:
		{
			break;
		}
		default:
			break;
	}
}

void ABaseBuildingObject::SetMeshType(EMeshType Type)
{
	switch (MeshType)
	{
	case Wood:
	{
		this->MeshType = EMeshType::Wood;
		Mesh->SetStaticMesh(MeshWood);
		break;
	}
	case Stone:
	{
		this->MeshType = EMeshType::Stone;
		Mesh->SetStaticMesh(MeshStone);
		break;
	}
	case Metal:
	{
		this->MeshType = EMeshType::Metal;
		Mesh->SetStaticMesh(MeshMetal);
		break;
	}
	default:
		break;
	}
}

