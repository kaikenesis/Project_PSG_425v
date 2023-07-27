#include "BuildingRoof.h"
#include "Global.h"

ABuildingRoof::ABuildingRoof()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &BuildComponents, "BuildComponents", Mesh);

	CHelpers::CreateSceneComponent(this, &CeilingSocket, "CeilingSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &CeilingSocket1, "CeilingSocket1", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket2, "CeilingSocket2", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket3, "CeilingSocket3", CeilingSocket);
	CHelpers::CreateSceneComponent(this, &CeilingSocket4, "CeilingSocket4", CeilingSocket);

	CHelpers::CreateSceneComponent(this, &RoofSocket, "RoofSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofSocket1, "RoofSocket1", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket2, "RoofSocket2", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket3, "RoofSocket3", RoofSocket);
	CHelpers::CreateSceneComponent(this, &RoofSocket4, "RoofSocket4", RoofSocket);

	CHelpers::CreateSceneComponent(this, &RoofWallSocket, "RoofWallSocket", BuildComponents);
	CHelpers::CreateSceneComponent(this, &RoofWallSocketLeft, "RoofWallSocketLeft", RoofWallSocket);
	CHelpers::CreateSceneComponent(this, &RoofWallSocketRight, "RoofWallSocketRight", RoofWallSocket);

	//Ceiling Set Location
	CeilingSocket1->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	CeilingSocket2->SetRelativeLocation(FVector(-300.f, 0.f, 150.f));
	CeilingSocket3->SetRelativeLocation(FVector(300.f, 0.f, -150.f));
	CeilingSocket4->SetRelativeLocation(FVector(0.f, 0.f, -150.f));

	//Roof Set Location
	RoofSocket1->SetRelativeLocation(FVector(300.f, 0.f, -300.f));
	RoofSocket2->SetRelativeLocation(FVector(0.f, -300.f, 0.f));
	RoofSocket3->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
	RoofSocket4->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));

	//RoofWall Set Location
	RoofWallSocketLeft->SetRelativeLocation(FVector(0.f, -150.f, 0.f));
	RoofWallSocketRight->SetRelativeLocation(FVector(0.f, 150.f, 0.f));
}