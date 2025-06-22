// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoBase.h"
#include "EnemigoAcuatico.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API AEnemigoAcuatico : public AEnemigoBase
{
	GENERATED_BODY()
	AEnemigoAcuatico();
protected:
	void BuscarJugador() override;
	void Moverse() override;
	void Atacar() override;
	void UsarHabilidadEspecial() override;

	UPROPERTY(EditAnywhere, Category = "Habilidad")
	TSubclassOf<class ABurbujaActor> BurbujaClass;

	FTimerHandle TimerHandle_BurbujaCooldown;
	bool bPuedeLanzarBurbuja = true;

	UFUNCTION()
	void ReiniciarCooldownBurbuja();

};
