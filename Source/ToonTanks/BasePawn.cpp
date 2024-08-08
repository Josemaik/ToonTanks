// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//replace rootcomponent for capsule component ( now capsule is going to be the root)
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	//create base mesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	//attach basemesh to root
	BaseMesh->SetupAttachment(CapsuleComp);

	//create turret mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	//attach turretmesh to basemesh
	TurretMesh->SetupAttachment(BaseMesh);

	//create spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); //worls space rotation
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); //only in yaw to be pararel with floor
	TurretMesh->SetWorldRotation( // interpolate to evoid fast rotations and to be more fluid
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			25.f
		)
	);
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	/*DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPointLocation,
		25.f,
		12,
		FColor::Red,
		false,
		3.f
	);*/
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	//todo visual/sound effects
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles,GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

// Called when the game starts or when spawned
//void ABasePawn::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ABasePawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	/*FVector DeltaLocation(0.f);
//	DeltaLocation.X = 2.f;
//	AddActorLocalOffset(DeltaLocation);*/
//}



