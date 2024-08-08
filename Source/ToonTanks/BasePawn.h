// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

	//solo es visible
	UPROPERTY(VisibleAnyWhere)
	int32 VisibleAnyWhereInt = 12;

	//visible y editable
	UPROPERTY(EditAnywhere)
	int32 EditAnyWhereInt = 12;

	//visible solo al seleccionar la instancia en el mundo
	UPROPERTY(VisibleInstanceOnly)
	int32 VisibleInstanceOnlyInt = 12;

	//visible solo al seleccionar en el editor ( lo contrario que el anterior)
	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultOnlyInt = 12;

	//editable solo desde el editor(default)
	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt = 7;

	//editable solo al seleccionar la instancia en el mundo
	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnlyInt = 8;

	//visible desde instancia y defecto / get/set desde event graph
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	int32 VisibleAnyWhereGraphInt = 14;

	//visible y editable desde instancia y defecto / get desde event graph
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EditAnyWhereGraphInt = 22;

protected:
	
	void RotateTurret(FVector LookAtTarget);
	void Fire();
private:
	//forward declaration
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	//is included by default
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	//visible y editable desde instancia y defecto / get y set desde event graph pero permite acceso desde private
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	int32 VisibleAnyWhereGraphPrivateInt = 14;

	//visible y editable desde instancia y defecto / get desde event graph
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	int32 EditAnyWhereGraphPrivateInt = 22;

	//projectile
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

public:	

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
