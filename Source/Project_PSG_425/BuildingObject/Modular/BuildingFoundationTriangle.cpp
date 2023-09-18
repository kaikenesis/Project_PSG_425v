#include "BuildingFoundationTriangle.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ABuildingFoundationTriangle::ABuildingFoundationTriangle()
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

	CHelpers::CreateSceneComponent(this, &FoundationSockets, "FoundationSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationSocket1, "FoundationSocket1", FoundationSockets);
	CHelpers::CreateSceneComponent(this, &FoundationSocket2, "FoundationSocket2", FoundationSockets);
	CHelpers::CreateSceneComponent(this, &FoundationSocket3, "FoundationSocket3", FoundationSockets);

	CHelpers::CreateSceneComponent(this, &FoundationTriangleSockets, "FoundationTriangleSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket1, "FoundationTriangleSocket1", FoundationTriangleSockets);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket2, "FoundationTriangleSocket2", FoundationTriangleSockets);
	CHelpers::CreateSceneComponent(this, &FoundationTriangleSocket3, "FoundationTriangleSocket3", FoundationTriangleSockets);

	CHelpers::CreateSceneComponent(this, &WallSockets, "WallSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &WallSocket1, "WallSocket1", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket2, "WallSocket2", WallSockets);
	CHelpers::CreateSceneComponent(this, &WallSocket3, "WallSocket3", WallSockets);

	CHelpers::CreateSceneComponent(this, &RampSockets, "RampSockets", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RampSocket1, "RampSocket1", RampSockets);
	CHelpers::CreateSceneComponent(this, &RampSocket2, "RampSocket2", RampSockets);
	CHelpers::CreateSceneComponent(this, &RampSocket3, "RampSocket3", RampSockets);

	// Set BuildCollision
	BuildCollision1->SetBoxExtent(FVector(125.f, 20.f, 84.f));
	BuildCollision1->SetRelativeLocation(FVector(0.f, 65.f, 0.f));

	BuildCollision2->SetBoxExtent(FVector(125.f, 20.f, 84.f));
	BuildCollision2->SetRelativeLocation(FVector(56.29f, -32.5f, 0.f));
	BuildCollision2->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	BuildCollision3->SetBoxExtent(FVector(125.f, 20.f, 84.f));
	BuildCollision3->SetRelativeLocation(FVector(-56.29f, -32.5f, 0.f));
	BuildCollision3->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	BuildCollision4->SetBoxExtent(FVector(80.f, 20.f, 84.f));
	BuildCollision4->SetRelativeLocation(FVector(0.f, 25.f, 0.f));

	BuildCollision5->SetBoxExtent(FVector(60.f, 20.f, 84.f));
	BuildCollision5->SetRelativeLocation(FVector(0.f, -15.f, 0.f));

	BuildCollision6->SetBoxExtent(FVector(40.f, 30.f, 84.f));
	BuildCollision6->SetRelativeLocation(FVector(0.f, -65.f, 0.f));

	// Set Foundation Location & Rotation
	FoundationSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	FoundationSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	FoundationSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	FoundationSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	FoundationSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// Set FoundationTriangle Location & Rotation
	FoundationTriangleSocket1->SetRelativeLocation(FVector(149.98f, -86.59f, 0.f));
	FoundationTriangleSocket1->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

	FoundationTriangleSocket2->SetRelativeLocation(FVector(-149.98f, -86.59f, 0.f));
	FoundationTriangleSocket2->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	FoundationTriangleSocket3->SetRelativeLocation(FVector(0.f, 173.2f, 0.f));
	FoundationTriangleSocket3->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Set Wall Location & Rotation
	WallSocket1->SetRelativeLocation(FVector(75.f, -43.3f, 235.f));
	WallSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	WallSocket2->SetRelativeLocation(FVector(-75.f, -43.3f, 235.f));
	WallSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	WallSocket3->SetRelativeLocation(FVector(0.f, 86.6f, 235.f));

	// Set Ramp Location & Rotation
	RampSocket1->SetRelativeLocation(FVector(204.85f, -118.27f, 0.f));
	RampSocket1->SetRelativeRotation(FRotator(0.f, -120.f, 0.f));

	RampSocket2->SetRelativeLocation(FVector(-204.85f, -118.27f, 0.f));
	RampSocket2->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));

	RampSocket3->SetRelativeLocation(FVector(0.f, 236.6f, 0.f));

	// Set EBuildType
	BuildType = EBuildType::FoundationTriangle;
}
