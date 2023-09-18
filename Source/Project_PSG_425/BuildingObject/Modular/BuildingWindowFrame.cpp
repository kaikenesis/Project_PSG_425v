#include "BuildingWindowFrame.h"
#include "Global.h"

ABuildingWindowFrame::ABuildingWindowFrame()
{
	// CreateComponent
	CHelpers::CreateSceneComponent(this, &WindowSocket, "WindowSocket", BuildComponents);

}
