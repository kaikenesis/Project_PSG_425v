#include "MontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UMontagesComponent::UMontagesComponent()
{

}


void UMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is Not set");
		return;
	}

	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	if (ownerCharacter)
	{
		UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(ownerCharacter);
		if (actionComp)
		{
			actionComp->OnActionTypeChanged.AddDynamic(this, &UMontagesComponent::ActionTypeChanged);
			actionComp->OnDoSubAction.AddDynamic(this, &UMontagesComponent::DoSubAction);
		}
	}

	
	//{ {0,1,2}, {0,1}, {0,1}}
	TArray<FMontageData*> datas;
	datas.Empty();

	DataTable->GetAllRows<FMontageData>("", datas);

	int32 size = (int32)EStateType::Max + (int32)EActionType::Max;

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		for (int32 j = 0; j < (int32)EStateType::Max; j++)
		{
			for (const auto& data : datas)
			{
				if ((EActionType)i == data->ActionType && (EStateType)j == data->StateType)
				{
					int num = ((i + 1) * (j + 1)) - 1;
					Datas[num] = data;

					break;
				}
			}
		}
	}
}

void UMontagesComponent::PlayAnimMontage(EActionType InActionType, EStateType InStateType)
{
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(ownerCharacter);

	int num = ((int32)InActionType + 1) * ((int32)InStateType + 1) - 1;
	FMontageData* data = Datas[num];

	if (!!data && !!data->AnimMontage)
	{
		ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
	}
}

void UMontagesComponent::PlayRoll()
{
	PlayAnimMontage(CurrentActionType, EStateType::Roll);
}

void UMontagesComponent::PlayEvade()
{
	PlayAnimMontage(CurrentActionType, EStateType::Evade);
}

void UMontagesComponent::PlayBlock()
{
	PlayAnimMontage(CurrentActionType, EStateType::Block);
}

void UMontagesComponent::PlayHitted()
{
	PlayAnimMontage(CurrentActionType, EStateType::Hitted);
}

void UMontagesComponent::PlayDead()
{
	PlayAnimMontage(CurrentActionType, EStateType::Dead);
}

void UMontagesComponent::ActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CurrentActionType = InNewType;
}

void UMontagesComponent::DoSubAction(bool InSubAction)
{
	IsSubAction = InSubAction;
}
