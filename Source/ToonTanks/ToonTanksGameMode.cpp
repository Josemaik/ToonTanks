// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tanqueee muertoooooo"));
		Tank->HandleDestruction();
		/*auto tankplayercontroller = Tank->GetTankPlayerController();*/
		if (ToonTanksPlayerController)
		{
			/*Tank->DisableInput(tankplayercontroller);
			Tank->GetTankPlayerController()->bShowMouseCursor = false;*/
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Torretaaaaaaaa muertaaaaa"));
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	//initialize num towers on the level
	TargetTowers = GetTargetTowersCount();

	FVector PawnSpawnLocation = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	Tank->SetSpawnPoint(PawnSpawnLocation);

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();
	
	//se deshabilita el input al princcipio
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnabledTimerHandle;
		FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			PlayerEnabledTimerHandle,
			PlayerEnabledTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

void AToonTanksGameMode::SpawnTank()
{
	Tank->Spawn();
	ToonTanksPlayerController->SetPlayerEnabledState(true);
}