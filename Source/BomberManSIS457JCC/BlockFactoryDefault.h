// BlockFactoryDefault.h
#pragma once

#include "CoreMinimal.h"
#include "BlockFactory.h"         // Incluye la f�brica abstracta
#include "BlockFactoryDefault.generated.h"

/**
 * UBlockFactoryDefault (ConcreteCreator)
 *
 *   - Hereda de UBlockFactory.
 *   - Implementa FabricarBloque_Implementation(...) con un switch sobre ETipoBloque.
 *   - Seg�n el valor de ETipoBloque, elige la UClass concreta (por ejemplo, ABloqueMadera::StaticClass())
 *     y hace World->SpawnActor<ABloqueBase>(ClaseConcreta, SpawnTransform).
 */
UCLASS()
class BOMBERMANSIS457JCC_API UBlockFactoryDefault : public UBlockFactory
{
    GENERATED_BODY()

public:
    UBlockFactoryDefault() : UBlockFactory() {}

    /**
     * Aqu� implementamos la l�gica real de creaci�n (Factory Method)
     */
    virtual ABloqueBase* FabricarBloque_Implementation(
        ETipoBloque Tipo,
        const FTransform& SpawnTransform,
        AActor* Owner
    ) const override;
};
