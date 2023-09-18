#include "BaseBuildingObject.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
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
	
	InitOverlapSettings();

	if (!!BuildingObjectHandle.DataTable)
		BuildingObjectSettings = BuildingObjectHandle.DataTable->FindRow<FBuildingObjectSettings>(BuildingObjectHandle.RowName, "");

	if (!!BuildingObjectSettings->StaticMesh)
		Mesh->SetStaticMesh(BuildingObjectSettings->StaticMesh);

	FTransform transform;
	FVector location = FVector(0.f, 0.f, 0.f);
	FRotator rotation = FRotator(0.f, 0.f, 0.f);
	FVector scale = FVector(1.f, 1.f, 1.f);

	transform = UKismetMathLibrary::MakeTransform(location, rotation, scale);

	if (BuildingObjectSettings->CorrectMeshTransform.Equals(transform) == false)
		Mesh->SetRelativeTransform(BuildingObjectSettings->CorrectMeshTransform);
}

void ABaseBuildingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuildingObject::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsBuilded == false)
	{
		ABaseBuildingObject* otherBuildObject = Cast<ABaseBuildingObject>(OtherActor);
		if (!!otherBuildObject)
		{
			UBoxComponent* boxComp = Cast<UBoxComponent>(OtherComp);
			if(!!boxComp)
				OverlapActors.Add(OtherActor);
		}

		if (Cast<ACharacter>(OtherActor))
			OverlapActors.Add(OtherActor);

		if (OverlapActors.Num() > 0)
			SetCanBeBuilt(false);

		CLog::Print("OverlapActor : " + OverlapActors.Num());
	}
}

void ABaseBuildingObject::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsBuilded == false)
	{
		ABaseBuildingObject* otherBuildObject = Cast<ABaseBuildingObject>(OtherActor);
		if (!!otherBuildObject)
		{
			UBoxComponent* boxComp = Cast<UBoxComponent>(OtherComp);
			if (!!boxComp)
				if (OverlapActors.Contains(OtherActor))
					OverlapActors.RemoveSingle(OtherActor);
		}


		if (Cast<ACharacter>(OtherActor))
			if (OverlapActors.Contains(OtherActor))
				OverlapActors.RemoveSingle(OtherActor);

		if (OverlapActors.Num() < 1)
			SetCanBeBuilt(true);

		CLog::Print("OverlapActor : " + OverlapActors.Num());
	}
}

void ABaseBuildingObject::SetCanBuild()
{
	SetCanBeBuilt(true);
}

void ABaseBuildingObject::SetCanNotBuild()
{
	SetCanBeBuilt(false);
}

void ABaseBuildingObject::SetCanBeBuilt(bool InCanBeBuilt)
{
	bCanBuild = InCanBeBuilt;

	if(bCanBuild == true)
		Mesh->SetMaterial(0, CanBuildMaterialInterface);
	else
		Mesh->SetMaterial(0, CanNotBuildMaterialInterface);
}

void ABaseBuildingObject::InitOverlapSettings()
{
	TArray<USceneComponent*> childComps;
	Mesh->GetChildrenComponents(true, childComps);

	for (const auto& childComp : childComps)
	{
		UBoxComponent* boxComp = Cast<UBoxComponent>(childComp);

		if (!!boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuildingObject::OnComponentBeginOverlap);
			boxComp->OnComponentEndOverlap.AddDynamic(this, &ABaseBuildingObject::OnComponentEndOverlap);
		}
	}
}
