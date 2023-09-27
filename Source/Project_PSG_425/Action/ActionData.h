#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActionData_Spawned.h"
#include "ActionData.generated.h"

UCLASS()
class PROJECT_PSG_425_API UActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwnerCharacter, UActionData_Spawned** OutSpawned);

private:
	FString GetCustomActorLabel(class ACharacter* InOwnerCharacter, FString ImMiddleName);

public:
	UPROPERTY(EditAnywhere, Category = "Attachment")
		TSubclassOf<class AAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		TSubclassOf<class AEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TSubclassOf<class ADoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;
};
