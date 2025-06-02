// BloqueTipos.h
#pragma once

#include "CoreMinimal.h"
#include "BloqueTipos.generated.h"

/**
 * ETipoBloque
 *
 * Enumeraci�n de los tipos de bloque que la f�brica podr� instanciar.
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
