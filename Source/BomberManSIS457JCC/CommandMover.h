#pragma once

#include "ICommand.h"

class AEnemigoBase;

class CommandMover : public ICommand
{
    AEnemigoBase* Receptor;
public:
    CommandMover(AEnemigoBase* InReceptor);
    void Ejecutar() override;
    void Deshacer() override;
};