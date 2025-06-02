// ULaberintoBuilder.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ULaberintoBuilder.generated.h"

UCLASS(Abstract)
class BOMBERMANSIS457JCC_API ULaberintoBuilder : public UObject
{
    GENERATED_BODY()
public:
    virtual void ConstruirLaberinto() {}
    virtual void ConstruirBloque(int fila, int columna) {}
    virtual void ConstruirPuerta(int filaDesde, int colDesde, int filaHasta, int colHasta) {}
    virtual class AALaberinto* ObtenerLaberinto() { return nullptr; }

};
