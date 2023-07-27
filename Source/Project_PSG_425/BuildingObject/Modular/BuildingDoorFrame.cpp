#include "BuildingDoorFrame.h"
#include "Global.h"

ABuildingDoorFrame::ABuildingDoorFrame()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &DoorSocket, "DoorSocket", BuildComponents);
}