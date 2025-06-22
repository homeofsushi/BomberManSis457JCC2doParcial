// Source\BomberManSIS457JCC\BloqueComponent.h
#pragma once

#include "UObject/Interface.h"
#include "BloqueComponent.generated.h"

// Esta macro declara la interfaz para Unreal
UINTERFACE(MinimalAPI)
class UBloqueComponent : public UInterface
{
    GENERATED_BODY()
};

// Esta es la interfaz C++ pura que implementar�n tus clases
class IBloqueComponent
{
    GENERATED_BODY()

public:
    // M�todo puro que deben implementar los bloques y composites
    virtual void RecibirDanio(int32 Danio) = 0;
    // Puedes agregar m�s m�todos comunes aqu�
};