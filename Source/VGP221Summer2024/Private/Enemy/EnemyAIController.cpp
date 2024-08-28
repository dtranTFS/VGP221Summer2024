// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!PawnSensing) {
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing2"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(StartingBehaviourTree);

	if(PawnSensing)
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	AFPSCharacter* player = Cast<AFPSCharacter>(PlayerPawn);
	if (!player) return;

	// Do some logic if it is the player
	SetCanSeePlayer(true, player);

	// Retriggerable Delay
	RunTriggerableTimer();
}

void AEnemyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player)
{
	UBlackboardComponent* blackboard = GetBlackboardComponent();
	blackboard->SetValueAsBool(FName("Can See Player"), SeePlayer);
	if (SeePlayer) {
		blackboard->SetValueAsObject(FName("Player Target"), Player);
	}
}

void AEnemyAIController::RunTriggerableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}
