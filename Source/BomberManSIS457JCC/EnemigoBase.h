// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemigoBase.generated.h"

UCLASS(Abstract)
class BOMBERMANSIS457JCC_API AEnemigoBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigoBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Método template
	virtual void TickComportamiento();

	// Pasos variables
	virtual void BuscarJugador() PURE_VIRTUAL(AEnemigoBase::BuscarJugador,);
	virtual void Moverse() PURE_VIRTUAL(AEnemigoBase::Moverse, );
	virtual void Atacar() PURE_VIRTUAL(AEnemigoBase::Atacar, );

	virtual void Volar() {}; //P mi enemigo volador
	virtual void Esconderse() {}; //Pa mi enemigo terrestre
	virtual void UsarHabilidadEspecial() {}; // Pa mi enemigo acuatico que lance burbujas o algo así

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	APawn* Objetivo;

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

};
