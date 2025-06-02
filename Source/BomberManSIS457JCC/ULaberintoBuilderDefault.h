// ULaberintoBuilderDefault.h
#pragma once

#include "CoreMinimal.h"
#include "ULaberintoBuilder.h"
#include "ALaberinto.h"
#include "BloqueTipos.h" // Asegúrate de que aquí está ETipoBloque
#include "ULaberintoBuilderDefault.generated.h"

UCLASS()
class BOMBERMANSIS457JCC_API ULaberintoBuilderDefault : public ULaberintoBuilder
{
    GENERATED_BODY()
public:
    ULaberintoBuilderDefault();

    virtual void ConstruirLaberinto() override;
    // ULaberintoBuilderDefault.h

    // ... otras declaraciones ...

public:
    void ConstruirBloque(int fila, int columna, ETipoBloque Tipo);
    void ConstruirBloque(int fila, int columna);


    virtual void ConstruirPuerta(int filaDesde, int colDesde, int filaHasta, int colHasta) override;
    virtual AALaberinto* ObtenerLaberinto() override;
    TMap<FIntPoint, FVector2D> OffsetAleatorioPorCelda;
    // ULaberintoBuilderDefault.h
    UPROPERTY()
    int Filas = 0;
    UPROPERTY()
    int Columnas = 0;
    UPROPERTY()
    FVector LaberintoOffset;

    const int ColumnaInicioDerecha = Columnas / 2; // 5 si Columnas=10
    const int ColumnaFinDerecha = Columnas;        // 10

private:
    AALaberinto* LaberintoActual;
    int BloquesCreados;
    int MaxBloques;
};
