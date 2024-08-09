// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_ToonTanks.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AHUD_ToonTanks : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Show_Puntuation();
};
