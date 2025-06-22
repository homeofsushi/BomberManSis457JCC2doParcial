// Source\BomberManSIS457JCC\BloqueComposite.cpp
#include "BloqueComposite.h"

void ABloqueComposite::RecibirDanio(int32 Danio)
{
    for (auto& Hijo : Hijos)
    {
        if (Hijo)
        {
            Hijo->RecibirDanio(Danio);
        }
    }
}

void ABloqueComposite::AgregarHijo(const TScriptInterface<IBloqueComponent>& Hijo)
{
    Hijos.Add(Hijo);
}

void ABloqueComposite::EliminarHijo(const TScriptInterface<IBloqueComponent>& Hijo)
{
    Hijos.Remove(Hijo);
}