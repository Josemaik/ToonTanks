// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerControl; }
	void SetSpawnPoint(FVector spawnpoint);
	void Spawn();
	bool bAlive = true;

	void SetHealth(float life);
	void Upgrade();
	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = "true"))
	void Increase_TankXp();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 45.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int NumBullets = 5;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int XPLevel = 0;

	void Move(float Value);
	void Turn(float Value);
	void Fire();

	APlayerController* TankPlayerControl;

	FVector SpawnPoint;

	class UHealthComponent* healthcomponent;
};
