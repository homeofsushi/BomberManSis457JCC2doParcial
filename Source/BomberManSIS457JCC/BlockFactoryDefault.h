// BlockFactoryDefault.h
#pragma once

#include "CoreMinimal.h"
#include "BlockFactory.h"         // Incluye la fábrica abstracta
#include "BlockFactoryDefault.generated.h"

/**
 * UBlockFactoryDefault (ConcreteCreator)
 *
 *   - Hereda de UBlockFactory.
 *   - Implementa FabricarBloque_Implementation(...) con un switch sobre ETipoBloque.
 *   - Según el valor de ETipoBloque, elige la UClass concreta (por ejemplo, ABloqueMadera::StaticClass())
 *     y hace World->SpawnActor<ABloqueBase>(ClaseConcreta, SpawnTransform).
 */
UCLASS()
class BOMBERMANSIS457JCC_API UBlockFactoryDefault : public UBlockFactory
{
    GENERATED_BODY()

public:
    UBlockFactoryDefault() : UBlockFactory() {}

    /**
     * Aquí implementamos la lógica real de creación (Factory Method)
     */
    virtual ABloqueBase* FabricarBloque_Implementation(
        ETipoBloque Tipo,
        const FTransform& SpawnTransform,
        AActor* Owner
    ) const override;
};
