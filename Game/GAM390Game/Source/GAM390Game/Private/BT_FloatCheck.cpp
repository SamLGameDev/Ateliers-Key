// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_FloatCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Operator.h"

UBT_FloatCheck::UBT_FloatCheck()
{
	//make it so only float BB keys can be selected
	m_FloatKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBT_FloatCheck, m_FloatKey));
	bNotifyTick = false;
}

bool UBT_FloatCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();

	//Check the input operator, and compare the input value and the key value against it

	const float keyValue = blackBoard->GetValueAsFloat(m_FloatKey.SelectedKeyName);

	if (!m_Operation) {
		return false;
	}

	if (m_Operation->Compare(keyValue, m_CheckValue)) {
		return true;
	}
	return false;

}

void UBT_FloatCheck::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	//Ensure key exists

	const UBlackboardData* bBAsset = GetBlackboardAsset();
	if (ensure(bBAsset)) {
		m_FloatKey.ResolveSelectedKey(*bBAsset);
	}
}
