// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloqueTipos.h"
#include "BloqueBase.generated.h"

UCLASS()
class BOMBERMANSIS457JCC_API ABloqueBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloqueBase();
	/** Cada subclase concreta implementa esto para configurar su malla, material, colisión, etc.*/
	virtual void InitializeBlock() PURE_VIRTUAL(ABloqueBase::InitializeBlock, );

	/**
	 * Cada subclase concreta debe implementar Clone() para devolver
	 * una copia idéntica de sí misma (para Prototype).
	 */
	virtual ABloqueBase* Clone(const FVector& NuevaPosicion);


	ETipoBloque TipoBloque;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
