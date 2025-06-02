// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloqueBase.h"
#include "ALaberinto.generated.h"

UCLASS()
class BOMBERMANSIS457JCC_API AALaberinto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AALaberinto();

public:
	void InicializarMatriz(int Filas, int Columnas);
	// Métodos y propiedades para almacenar y manipular los bloques y puertas
	TArray<TArray<ABloqueBase*>> MatrizBloques;
	// Métodos para añadir bloques, puertas, etc.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
