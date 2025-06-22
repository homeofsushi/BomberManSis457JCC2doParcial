// Fill out your copyright notice in the Description page of Project Settings.
// IJuegoFacade.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bomba.h"
#include "IJuegoFacade.generated.h"

// IJuegoFacade.h
UINTERFACE(MinimalAPI)
class UJuegoFacade : public UInterface
{
    GENERATED_BODY()
};

class IJuegoFacade
{
    GENERATED_BODY()
public:
    virtual void ConstruirLaberinto() = 0;
    virtual void SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation) = 0;
};