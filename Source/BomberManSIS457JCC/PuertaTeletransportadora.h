// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "PuertaTeletransportadora.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API APuertaTeletransportadora : public ABloqueBase
{
	GENERATED_BODY()
	
private:
    /** Componente de colisi�n para detectar overlaps */
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionComp;

    /** Componente de malla para representar la puerta */
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    /** Part�culas que se reproducen al teletransportar */
    UPROPERTY()
    UParticleSystem* TeleportEffect;

    /** Colecci�n de todas las puertas que existen en escena (para elegir destino) */
    TArray<APuertaTeletransportadora*> PuertasTeletransportadoras;

    /** Conjunto de personajes a los que no queremos volver a teletransportar inmediatamente */
    TSet<ACharacter*> IgnoradosTemporalmente;

public:
    APuertaTeletransportadora();

    /**
     * Configura mesh, colisi�n y enlaza eventos.
     * Se llama desde la f�brica justo despu�s de spawnear este actor.
     */
    virtual void InitializeBlock() override;

    /**
     * Llamar despu�s de crear todas las puertas para pasarles la lista completa.
     */
    void SetPuertasTeletransportadoras(const TArray<APuertaTeletransportadora*>& TodasPuertas);

protected:
    /** Handler de begin overlap para teletransportar al personaje */
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    /** Teletransporta al personaje a una puerta aleatoria distinta de esta */
    void TeletransportarPersonaje(ACharacter* Personaje);
};
