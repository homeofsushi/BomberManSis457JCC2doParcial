// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomba.h"
#include "UObject/NoExportTypes.h"
#include "BombaFactory.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOMBERMANSIS457JCC_API UBombaFactory : public UObject
{
	GENERATED_BODY()
public:
	virtual ABomba* CrearBomba(UWorld* World, const FVector& SpawnLocation, const FRotator& SpawnRotation) PURE_VIRTUAL(UBombFactory::CrearBomba, return nullptr;);
	
};
