// ULaberintoBuilderDefault.cpp

#include "ULaberintoBuilderDefault.h"
#include "BlockFactoryDefault.h"
#include "BlockFactory.h"
#include "Engine/World.h"
#include "ALaberinto.h"
#include "BloqueBase.h"

const FVector LaberintoOffset(-900.f, -500.f, 0.f); // Offset para centrar el laberinto

ULaberintoBuilderDefault::ULaberintoBuilderDefault()
{
    LaberintoActual = nullptr;
    BloquesCreados = 0;
    MaxBloques = (Filas * Columnas) * 0.4f; // 40% del espacio
}

void ULaberintoBuilderDefault::ConstruirLaberinto()
{
    // 1) Spawnear actor AALaberinto en LaberintoOffset:
    UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
    FTransform Transform(LaberintoOffset);
    LaberintoActual = World->SpawnActor<AALaberinto>(AALaberinto::StaticClass(), Transform);
    if (!LaberintoActual)
    {
        UE_LOG(LogTemp, Error, TEXT("No se pudo spawnear AALaberinto."));
        return;
    }
    LaberintoActual->InicializarMatriz(Filas, Columnas);

    // 2) Elegir posiciones únicas para monedas y puertas en la mitad derecha
    TSet<FIntPoint> PosMonedas;
    TSet<FIntPoint> PosPuertas;
    int totalDerecha = Filas * (ColumnaFinDerecha - ColumnaInicioDerecha);

    // 2a) Posiciones para 3 monedas
    while (PosMonedas.Num() < 3) {
        int idx = FMath::RandRange(0, totalDerecha - 1);
        int fila = idx / (ColumnaFinDerecha - ColumnaInicioDerecha);
        int col = ColumnaInicioDerecha + (idx % (ColumnaFinDerecha - ColumnaInicioDerecha));
        FIntPoint p(fila, col);
        PosMonedas.Add(p);
    }
    // 2b) Posiciones para 2 puertas (sin repetir monedas)
    while (PosPuertas.Num() < 2) {
        int idx = FMath::RandRange(0, totalDerecha - 1);
        int fila = idx / (ColumnaFinDerecha - ColumnaInicioDerecha);
        int col = ColumnaInicioDerecha + (idx % (ColumnaFinDerecha - ColumnaInicioDerecha));
        FIntPoint p(fila, col);
        if (!PosMonedas.Contains(p))
            PosPuertas.Add(p);
    }

    // 3) GENERAR MITAD DERECHA con ConstruirBloque(fila, columna, tipo)
    for (int fila = 0; fila < Filas; ++fila)
    {
        for (int col = ColumnaInicioDerecha; col < ColumnaFinDerecha; ++col)
        {
            ETipoBloque tipoBloque;
            FIntPoint cell(fila, col);

            if (PosMonedas.Contains(cell))
                tipoBloque = ETipoBloque::Coin;
            else if (PosPuertas.Contains(cell))
                tipoBloque = ETipoBloque::Puerta;
            else {
                TArray<ETipoBloque> arr = { ETipoBloque::Madera, ETipoBloque::Ladrillo, ETipoBloque::Acero };
                tipoBloque = arr[FMath::RandRange(0, arr.Num() - 1)];
            }

            // AQUÍ es la llamada relevante:
            ConstruirBloque(fila, col, tipoBloque);
        }
    }


    // 4) CLONAR A MITAD IZQUIERDA: usamos las mismas fórmulas de cuadrícula
    float EspaciadoX = (1000.f - (-1800.f)) / (Columnas - 1);
    float EspaciadoY = (1400.f - (-1400.f)) / (Filas - 1);

    for (int fila = 0; fila < Filas; ++fila)
    {
        for (int col = ColumnaInicioDerecha; col < ColumnaFinDerecha; ++col)
        {
            ABloqueBase* bloqueOriginal = LaberintoActual->MatrizBloques[fila][col];
            if (!bloqueOriginal)
                continue;

            // 4a) Calculamos la columna espejo
            int colIzquierda = ColumnaInicioDerecha - (col - ColumnaInicioDerecha) - 1;
            if (colIzquierda < 0 || colIzquierda >= ColumnaInicioDerecha)
                continue;

            // 4b) Clonar con Prototype
            ABloqueBase* bloqueClonado = bloqueOriginal->Clone();
            if (!bloqueClonado)
                continue;

            // 4c) Calcular nueva posición (X, Y, Z) para el clon,
            float x_clon = -1800.f + colIzquierda * EspaciadoX;
            float y_clon = -1400.f + fila * EspaciadoY;

            // 4d) Determinar tipo de bloque para ajustar escala y Z
            ETipoBloque tipoClonado = bloqueOriginal->TipoBloque;

            float z_clon = 0.f;
            FVector escalaClon(1.f, 1.f, 2.f);

            if (tipoClonado == ETipoBloque::Coin) {
                z_clon = 150.f;
                escalaClon = FVector(1.f, 1.f, 1.f);
            }
            if (tipoClonado == ETipoBloque::Puerta) {
                z_clon = 50.f; // Moneda de 50 de alto, pivote en centro
                escalaClon = FVector(1.f, 1.f, 1.f);
            }

            bloqueClonado->SetActorLocation(FVector(x_clon, y_clon, z_clon));
            bloqueClonado->SetActorScale3D(escalaClon);
            bloqueClonado->TipoBloque = tipoClonado;

            // 4e) Copiar rotación (por si puerta o bloque tienen rotación distinta)
            FRotator rotOrig = bloqueOriginal->GetActorRotation();
            bloqueClonado->SetActorRotation(rotOrig);

            // 4f) Adjuntar al laberinto (opcional, para mantener jerarquía en el Outliner)
            bloqueClonado->AttachToActor(LaberintoActual, FAttachmentTransformRules::KeepWorldTransform);

            // 4g) Guardar el clon en la matriz
            LaberintoActual->MatrizBloques[fila][colIzquierda] = bloqueClonado;
        }
    }
}

void ULaberintoBuilderDefault::ConstruirBloque(int fila, int columna, ETipoBloque Tipo)
{
    if (!LaberintoActual)
        return;

    UBlockFactoryDefault* Factory = NewObject<UBlockFactoryDefault>();

    float EspaciadoX = (1000.f - (-1800.f)) / (Columnas - 1);
    float EspaciadoY = (1400.f - (-1400.f)) / (Filas - 1);

    float x = -1800.f + columna * EspaciadoX;
    float y = -1400.f + fila * EspaciadoY;
    float z = 0.f;
    FVector Escala(1.f, 1.f, 2.f);

    if (Tipo == ETipoBloque::Coin) {
        z = 150.f; // Moneda de 50 de alto, pivote en centro
        Escala = FVector(1.f, 1.f, 1.f);
    }
    if (Tipo == ETipoBloque::Puerta) {
        z = 50.f; // Moneda de 50 de alto, pivote en centro
        Escala = FVector(1.f, 1.f, 1.f);
    }

    FVector Posicion(x, y, z);
    FTransform Transform(Posicion);

    ABloqueBase* bloque = Factory->FabricarBloque(Tipo, Transform, LaberintoActual);
    if (!bloque)
        return;

    bloque->SetActorScale3D(Escala);
    bloque->TipoBloque = Tipo;

    LaberintoActual->MatrizBloques[fila][columna] = bloque;
    ++BloquesCreados;
}

void ULaberintoBuilderDefault::ConstruirBloque(int fila, int columna)
{
    ConstruirBloque(fila, columna, ETipoBloque::Madera);
}

void ULaberintoBuilderDefault::ConstruirPuerta(int filaDesde, int colDesde, int filaHasta, int colHasta)
{
    // (Opcional) Si necesitas puertas que abarquen varias celdas, implementa aquí
}

AALaberinto* ULaberintoBuilderDefault::ObtenerLaberinto()
{
    return LaberintoActual;
}