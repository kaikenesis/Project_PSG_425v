#include "CraftRPGGameMode.h"
#include "Global.h"
#include "Characters/PlayerCharacter.h"

ACraftRPGGameMode::ACraftRPGGameMode()
{
	TSubclassOf<APawn> pawnAssetClass;
	CHelpers::GetClass<APawn>(&pawnAssetClass, "Class'/Script/Project_PSG_425.PlayerCharacter'");
	if (!!pawnAssetClass)
		DefaultPawnClass = pawnAssetClass;

	TSubclassOf<APlayerController> playerControllerClass;
	CHelpers::GetClass<APlayerController>(&playerControllerClass, "Class'/Script/Project_PSG_425.CraftRPGPlayerController'");
	if (!!playerControllerClass)
		PlayerControllerClass = playerControllerClass;
}