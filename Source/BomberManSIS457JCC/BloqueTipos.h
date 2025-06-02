// BloqueTipos.h
#pragma once

#include "CoreMinimal.h"
#include "BloqueTipos.generated.h"

/**
 * ETipoBloque
 *
 * Enumeración de los tipos de bloque que la fábrica podrá instanciar.
 */
UENUM()
enum class ETipoBloque : uint8
{
    Madera      UMETA(DisplayName = "BloqueMadera"),
    Ladrillo    UMETA(DisplayName = "BloqueLadrillo"),
    Acero       UMETA(DisplayName = "BloqueAcero"),
    Coin        UMETA(DisplayName = "Moneda"),
    Puerta      UMETA(DisplayName = "PuertaTeletransportadora")
};
