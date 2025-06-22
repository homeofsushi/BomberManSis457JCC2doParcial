// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IJuegoFacade.h"
#include "JuegoFacadeActor.generated.h"

// Forward declarations para evitar includes innecesarios en el header
class AALaberintoDirector;
class ULaberintoBuilderDefault;
class UBombaFactoryConcreta;

UCLASS()
class BOMBERMANSIS457JCC_API AJuegoFacadeActor : public AActor, public IJuegoFacade
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AJuegoFacadeActor();

    virtual void ConstruirLaberinto() override;
    virtual void SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation) override;

protected:
    virtual void BeginPlay() override;

private:
    // Referencias a los componentes principales del Facade
    AALaberintoDirector* Director;
    ULaberintoBuilderDefault* Builder;
    UBombaFactoryConcreta* BombFactory;
};