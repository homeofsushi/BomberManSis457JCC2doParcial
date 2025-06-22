// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoBase.h"
#include "EnemigoAereo.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API AEnemigoAereo : public AEnemigoBase
{
	GENERATED_BODY()
	AEnemigoAereo();
protected:
	void BuscarJugador() override;
	void Moverse() override;
	void Atacar() override;
	void Volar() override;
};
