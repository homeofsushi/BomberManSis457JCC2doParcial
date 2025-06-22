// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ICommand.h"

class Emisor
{
protected:
    ICommand* ComandoActual = nullptr;
public:
    void EstablecerComando(ICommand* NuevoComando) { ComandoActual = NuevoComando; }
    void EjecutarComando() { if (ComandoActual) ComandoActual->Ejecutar(); }
    void DeshacerComando() { if (ComandoActual) ComandoActual->Deshacer(); }
};