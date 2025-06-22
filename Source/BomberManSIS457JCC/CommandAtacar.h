// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ICommand.h"

class AEnemigoBase;

class CommandAtacar : public ICommand
{
    AEnemigoBase* Receptor;
public:
    CommandAtacar(AEnemigoBase* InReceptor);
    void Ejecutar() override;
    void Deshacer() override;
};