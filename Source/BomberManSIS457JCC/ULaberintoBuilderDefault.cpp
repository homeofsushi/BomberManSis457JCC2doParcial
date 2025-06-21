#include "ULaberintoBuilderDefault.h"
#include "BlockFactoryDefault.h"
#include "BlockFactory.h"
#include "Engine/World.h"
#include "ALaberinto.h"
#include "BloqueBase.h"
#include "Math/UnrealMathUtility.h"

const FVector LaberintoOffset(-900.f, -500.f, 0.f);


ULaberintoBuilderDefault::ULaberintoBuilderDefault()
{
    LaberintoActual = nullptr;
    BloquesCreados = 0;
    MaxBloques = (Filas * Columnas) * 0.4f;
}

void ULaberintoBuilderDefault::ConstruirLaberinto()
{
    // Parámetros de límites y espaciado
    const float xmin = -1800.f;
    const float xmax = 1000.f;
    const float ymin = -1400.f;
    const float ymax = 1400.f;
    const float EspaciadoX = 100.f;
    const float EspaciadoY = 100.f;
    Columnas = static_cast<int>((xmax - xmin) / EspaciadoX) + 1;
    Filas = static_cast<int>((ymax - ymin) / EspaciadoY) + 1;
    LaberintoOffset = FVector(xmin, ymin, 0.f);

    UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
    FTransform Transform(LaberintoOffset);
    LaberintoActual = World->SpawnActor<AALaberinto>(AALaberinto::StaticClass(), Transform);
    if (!LaberintoActual)
    {
        UE_LOG(LogTemp, Error, TEXT("No se pudo spawnear AALaberinto."));
        return;
    }
    LaberintoActual->InicializarMatriz(Filas, Columnas);

    // 1. Matriz temporal: 0=camino, 1=bloque, 2=moneda, 3=puerta
    TArray<TArray<int>> matriz;
    matriz.SetNum(Filas);
    for (int i = 0; i < Filas; ++i)
        matriz[i].Init(1, Columnas); // Todo bloque por defecto

    // 2. Generar caminos aleatorios en la mitad derecha
    int colIni = Columnas / 2;
    int colFin = Columnas;
    FRandomStream rng(FMath::Rand());

    for (int i = 0; i < Filas; ++i) {
        for (int j = colIni; j < colFin; ++j) {
            // Probabilidad de ser camino
            if (rng.FRand() < 0.50f)
                matriz[i][j] = 0;
        }
    }

    // 3. Agrupar bloques (opcional, refuerza grupos)
    for (int i = 1; i < Filas - 1; ++i) {
        for (int j = colIni + 1; j < colFin - 1; ++j) {
            int vecinos = 0;
            for (int di = -1; di <= 1; ++di)
                for (int dj = -1; dj <= 1; ++dj)
                    if (matriz[i + di][j + dj] == 1) vecinos++;
            if (vecinos >= 7) matriz[i][j] = 1;
        }
    }

    // 4. Colocar monedas y puertas aleatorias en caminos de la mitad derecha
    TArray<FIntPoint> caminos;
    for (int i = 0; i < Filas; ++i)
        for (int j = colIni; j < colFin; ++j)
            if (matriz[i][j] == 0)
                caminos.Add(FIntPoint(i, j));

    caminos.Sort([&](const FIntPoint& A, const FIntPoint& B) { return rng.FRand() < 0.5f; });

    int numMonedas = FMath::Min(3, caminos.Num());
    int numPuertas = FMath::Min(3, caminos.Num() - numMonedas);

    for (int k = 0; k < numMonedas; ++k)
        matriz[caminos[k].X][caminos[k].Y] = 2;

    for (int k = numMonedas; k < numMonedas + numPuertas; ++k)
        matriz[caminos[k].X][caminos[k].Y] = 3;

    // 5. Construir mitad derecha
    for (int i = 0; i < Filas; ++i) {
        for (int j = colIni; j < colFin; ++j) {
            ETipoBloque tipo;
            switch (matriz[i][j]) {
            case 1: {
                int r = rng.RandRange(0, 2);
                tipo = (r == 0) ? ETipoBloque::Madera : (r == 1) ? ETipoBloque::Ladrillo : ETipoBloque::Acero;
                break;
            }
            case 2: tipo = ETipoBloque::Coin; break;
            case 3: tipo = ETipoBloque::Puerta; break;
            default: continue;
            }
            ConstruirBloque(i, j, tipo);
        }
    }

    // 6. Clonar a la mitad izquierda (espejo)
    for (int i = 0; i < Filas; ++i) {
        for (int j = colIni; j < colFin; ++j) {
            int espejo = colIni - (j - colIni) - 1;
            if (espejo >= 0 && espejo < colIni) {
                ABloqueBase* original = LaberintoActual->MatrizBloques[i][j];
                if (original) {
                    float x_clon = xmin + espejo * EspaciadoX;
                    float y_clon = ymin + i * EspaciadoY;
                    FVector nuevaPosicion(x_clon, y_clon, original->GetActorLocation().Z);

                    ABloqueBase* clon = original->Clone(nuevaPosicion);
                    if (clon) {
                        clon->SetActorScale3D(original->GetActorScale3D());
                        clon->SetActorRotation(original->GetActorRotation());
                        clon->AttachToActor(LaberintoActual, FAttachmentTransformRules::KeepWorldTransform);
                        LaberintoActual->MatrizBloques[i][espejo] = clon;
                    }
                }
            }
        }
    }
}
// El resto de tus métodos (ConstruirBloque, etc.) no necesitan cambios.


void ULaberintoBuilderDefault::ConstruirBloque(int fila, int columna, ETipoBloque Tipo)
{
    if (!LaberintoActual)
        return;

    UBlockFactoryDefault* Factory = NewObject<UBlockFactoryDefault>();

    float EspaciadoX = 100.f; // Tamaño real del bloque en X
    float EspaciadoY = 100.f; // Tamaño real del bloque en Y

    float x = LaberintoOffset.X + columna * EspaciadoX;
    float y = LaberintoOffset.Y + fila * EspaciadoY;
    float z = 0.f;
    FVector Escala(1.f, 1.f, 2.f);

    if (Tipo == ETipoBloque::Coin) {
        z = 150.f;
        Escala = FVector(1.f, 1.f, 1.f);
    }
    if (Tipo == ETipoBloque::Puerta) {
        z = 50.f;
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
// Si no lo tienes, agrega esto en tu ULaberintoBuilderDefault.cpp

void ULaberintoBuilderDefault::ConstruirBloque(int fila, int columna) {
    ConstruirBloque(fila, columna, ETipoBloque::Madera);
}

void ULaberintoBuilderDefault::ConstruirPuerta(int filaDesde, int colDesde, int filaHasta, int colHasta) {
    // Implementación vacía o lógica de puertas
}

AALaberinto* ULaberintoBuilderDefault::ObtenerLaberinto() {
    return LaberintoActual;
}

