// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoBase.h"
#include "EnemigoTerrestre.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API AEnemigoTerrestre : public AEnemigoBase
{
	GENERATED_BODY()
	AEnemigoTerrestre();
protected:
	void BuscarJugador() override;
	void Moverse() override;
	void Atacar() override;
	void Esconderse() override;
public:
	// Vida del enemigo, editable en el editor y accesible en Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemigo")
	float Vida = 100.0f;
};
