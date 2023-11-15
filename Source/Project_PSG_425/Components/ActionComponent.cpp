#include "ActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Action/ActionData.h"
#include "Action/ActionData_Spawned.h"
#include "Action/Equipment.h"
#include "Action/DoAction.h"
#include "Action/Attachment.h"

UActionComponent::UActionComponent()
{

}


void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(ownerCharacter, &Datas[i]);
	}
}

void UActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->Unequip();

	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UActionComponent::SetOneHandShieldMode()
{
	SetMode(EActionType::OneHandShield);
}

void UActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UActionComponent::SetSubAction(bool InSubAction)
{
	bSubAction = InSubAction;

	if (IsMagicBallMode())
	{
		if (!!GetCurrentData() && !!GetCurrentData()->GetDoAction())
		{
			if (bSubAction == true)
				GetCurrentData()->GetDoAction()->OnAim();
			else
				GetCurrentData()->GetDoAction()->OffAim();
		}
	}

	if (OnDoSubAction.IsBound())
		OnDoSubAction.Broadcast(bSubAction);
}

void UActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (IsMagicBallMode())
	{
		if (!!GetCurrentData() && !!GetCurrentData()->GetDoAction())
			GetCurrentData()->GetDoAction()->DoAction();

		return;
	}


	if (IsSubAction() == false) // SubAction를 하고있지 않을때
	{
		//Main Action
		if (!!GetCurrentData() && !!GetCurrentData()->GetDoAction())
			GetCurrentData()->GetDoAction()->DoAction();

		return;
	}
	
	DoSubAction();
}

void UActionComponent::DoSubAction()
{
	//Sub Action
	if (!!GetCurrentData() && !!GetCurrentData()->GetDoSubAction())
		GetCurrentData()->GetDoSubAction()->DoAction();
}

void UActionComponent::OffAllCollisions()
{
	for (const auto& data : Datas)
	{
		if (data == nullptr)
			continue;

		if (data->GetAttachment() == nullptr)
			continue;

		data->GetAttachment()->OffCollisions();
	}
}

void UActionComponent::AbortByDamaged()
{
	CheckNull(GetCurrentData());
	CheckTrue(IsUnarmedMode());

	GetCurrentData()->GetEquipment()->Begin_Equip();
	GetCurrentData()->GetEquipment()->End_Equip();

	GetCurrentData()->GetDoAction()->Abort();
}

void UActionComponent::End_Dead()
{
	for (int i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!Datas[i] && !!Datas[i]->GetEquipment())
			Datas[i]->GetEquipment()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetAttachment())
			Datas[i]->GetAttachment()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetDoAction())
			Datas[i]->GetDoAction()->Destroy();
	}
}

void UActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false) //Unarmed가 아닌 Type을 장착하고 있었다면
	{
		if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}
	if (!!Datas[(int32)InNewType] && !!Datas[(int32)InNewType]->GetEquipment())
		Datas[(int32)InNewType]->GetEquipment()->Equip();

	ChangeType(InNewType);
}

void UActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}
