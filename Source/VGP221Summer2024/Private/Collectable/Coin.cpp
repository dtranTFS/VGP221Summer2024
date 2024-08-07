// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/Coin.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CoinMeshComponent) {
		CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
		CoinMeshComponent->SetupAttachment(CollisionComponent);
	}
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void ACoin::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("Coin OnCollect Called"));

	RotationRate = OnCollectRotationRate;
	// C++ version of delay node
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACoin::DeathTimerComplete, 0.5f, false);
}

void ACoin::DeathTimerComplete()
{
	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (HUD) {
		HUD->gameWidgetContainer->SetScoreText(Points);
	}

	Destroy();
}