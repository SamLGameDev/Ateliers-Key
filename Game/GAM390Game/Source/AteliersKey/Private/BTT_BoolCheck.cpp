// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_BoolCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Operator.h"

UBTT_BoolCheck::UBTT_BoolCheck()
{
	//make it so only float BB keys can be selected
	m_BoolKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_BoolCheck, m_BoolKey));
	bNotifyTick = false;
}

bool UBTT_BoolCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();

	//Check the input operator, and compare the input value and the key value against it

	const bool bkeyValue = blackBoard->GetValueAsBool(m_BoolKey.SelectedKeyName);

	if (!m_Operation) {
		return false;
	}

	if (m_Operation->Compare(bkeyValue, m_CheckValue)) {
		return true;
	}
	return false;

}

void UBTT_BoolCheck::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	//Ensure key exists

	const UBlackboardData* bBAsset = GetBlackboardAsset();
	if (ensure(bBAsset)) {
		m_BoolKey.ResolveSelectedKey(*bBAsset);
	}
}
