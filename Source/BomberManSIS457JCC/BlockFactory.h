// BlockFactory.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BloqueTipos.h"    // Aquí está tu enum ETipoBloque
#include "BloqueBase.h"     // Aquí está la clase abstrata ABloqueBase
#include "BlockFactory.generated.h"

/**
 * UBlockFactory (Creator abstracto)
 *
 *   - Esta clase hereda de UObject.
 *   - Declara el método virtual FabricarBloque, que deberá implementar la subclase.
 *   - FabricarBloque recibe:
 *       * ETipoBloque    → indica qué bloque se quiere crear
 *       * FTransform     → posición/rotación/escala donde se spawneará el bloque
 *       * AActor* Owner  → actor que “posee” la fábrica, para obtener GetWorld()
 *   - Devuelve un puntero a ABloqueBase (o nullptr si falla).
 */
UCLASS(Abstract, Blueprintable)
class BOMBERMANSIS457JCC_API UBlockFactory : public UObject
{
    GENERATED_BODY()

public:
    UBlockFactory() {}

    /**
     * FabricarBloque (Factory Method)
     * @param Tipo            : qué tipo de bloque queremos
     * @param SpawnTransform  : transform donde spawnearlo
     * @param Owner           : actor propietario para obtener GetWorld()
     * @return un ABloqueBase* recién creado (o nullptr si hubo error)
     */
    UFUNCTION(BlueprintNativeEvent, Category = "Factory")
    ABloqueBase* FabricarBloque( ETipoBloque Tipo, const FTransform& SpawnTransform, AActor* Owner) const;

    /**
     * Implementación pura: obliga a que la subclase concreta lo sobrescriba.
     */
    virtual ABloqueBase* FabricarBloque_Implementation(
        ETipoBloque Tipo,
        const FTransform& SpawnTransform,
        AActor* Owner
    ) const PURE_VIRTUAL(UBlockFactory::FabricarBloque_Implementation, return nullptr; );
};


