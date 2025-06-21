// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BombaFactory.h"
#include "Bomba.h"
#include "BombaFactoryConcreta.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API UBombaFactoryConcreta : public UBombaFactory
{
	GENERATED_BODY()
public:
	virtual ABomba* CrearBomba(UWorld* World, const FVector& SpawnLocation, const FRotator& SpawnRotation, EBombType Tipo);
	
};
