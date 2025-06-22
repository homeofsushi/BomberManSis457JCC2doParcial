// Source\BomberManSIS457JCC\BloqueComposite.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloqueComponent.h"
#include "BloqueComposite.generated.h"

UCLASS()
class BOMBERMANSIS457JCC_API ABloqueComposite : public AActor, public IBloqueComponent
{
    GENERATED_BODY()

public:
    // Lista de hijos (bloques o composites)
    UPROPERTY()
    TArray<TScriptInterface<IBloqueComponent>> Hijos;

    // Implementaci�n de la interfaz
    virtual void RecibirDanio(int32 Danio) override;

    // M�todos para gestionar hijos
    void AgregarHijo(const TScriptInterface<IBloqueComponent>& Hijo);
    void EliminarHijo(const TScriptInterface<IBloqueComponent>& Hijo);
};