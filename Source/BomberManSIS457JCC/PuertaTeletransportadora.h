// Source\BomberManSIS457JCC\PuertaTeletransportadora.h
#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PuertaTeletransportadora.generated.h"

/**
 * Puerta que teletransporta al personaje a otra puerta aleatoria.
 */
UCLASS()
class BOMBERMANSIS457JCC_API APuertaTeletransportadora : public ABloqueBase
{
    GENERATED_BODY()

private:
    /** Componente de colisión para detectar overlaps */
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionComp;

    /** Componente de malla para representar la puerta */
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    /** Lista de todas las puertas teletransportadoras */
    TArray<APuertaTeletransportadora*> PuertasTeletransportadoras;

public:
    APuertaTeletransportadora();

    /** Configura mesh, colisión y enlaza eventos */
    virtual void InitializeBlock() override;

    /** Asigna la lista de todas las puertas */
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