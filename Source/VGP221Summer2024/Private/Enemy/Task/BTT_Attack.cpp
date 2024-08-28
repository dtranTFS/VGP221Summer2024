// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTT_Attack.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFPSCharacter* playerCharacter = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Player Target")));
	if(!playerCharacter) return EBTNodeResult::Failed;

	float DamageAmount = 1.0f;
	AEnemyAIController* AIOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if(!AIOwner) return EBTNodeResult::Failed;

	playerCharacter->TakeDamage(DamageAmount, FDamageEvent(), AIOwner, AIOwner->GetPawn());

	return EBTNodeResult::Succeeded;
}
