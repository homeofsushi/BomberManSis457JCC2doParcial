// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomba.h"
#include "Emisor.h"
#include "JuegoFacadeActor.generated.h"

// Forward declarations para evitar includes innecesarios en el header
class AALaberintoDirector;
class ULaberintoBuilderDefault;
class UBombaFactoryConcreta;
class AEnemigoBase;
UCLASS()
class BOMBERMANSIS457JCC_API AJuegoFacadeActor : public AActor
{
    GENERATED_BODY()

public:
    AJuegoFacadeActor();

    void ConstruirLaberinto();
    void SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation);

    void OrdenarMoverEnemigo(AEnemigoBase* Enemigo);
    void OrdenarAtacarEnemigo(AEnemigoBase* Enemigo);

protected:
    virtual void BeginPlay() override;

private:
    AALaberintoDirector* Director;
    ULaberintoBuilderDefault* Builder;
    UBombaFactoryConcreta* BombFactory;
	Emisor* EmisorComandos;
};