// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//asegura que cualquier configuración de entrada que esté definida en la clase base también se ejecute
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//bind input mappings with functions
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}
void ATank::Fire()
{
	Super::Fire();
	if (NumBullets != 0)
	{
		--NumBullets;
	}
	UE_LOG(LogTemp, Warning, TEXT("Bullets: %i"), NumBullets)
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerControl)
	{
		FHitResult HitResult;
		TankPlayerControl->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);
		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			25.f,
			12,
			FColor::Red,
			false,
			-1.f
		);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerControl = Cast<APlayerController>(GetController());

	healthcomponent = FindComponentByClass<UHealthComponent>();
}
void ATank::Move(float Value)
{
	// 1 al pulsar W y -1 al pulsar S
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
	FVector DeltaLocation = FVector::ZeroVector;
	//X = Value * Deltatime * Speed
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); 
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	//Yaw = Value * DeltaTime * TurnRate
	DeltaRotator.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	AddActorLocalRotation(DeltaRotator, true);
}

void ATank::SetSpawnPoint(FVector spawnpoint)
{
	SpawnPoint = spawnpoint;
}
void ATank::Spawn()
{
	//restart health to 100
	if (healthcomponent)
	{
		healthcomponent->SetHealth(100);
	}

	NumBullets = 5;

	SetActorLocation(SpawnPoint);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	bAlive = true;
}
void ATank::SetHealth(float life)
{
	healthcomponent->SetHealth(0);
}