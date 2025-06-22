#include "CommandAtacar.h"
#include "EnemigoBase.h"

CommandAtacar::CommandAtacar(AEnemigoBase* InReceptor) : Receptor(InReceptor) {}

void CommandAtacar::Ejecutar() { if (Receptor) Receptor->Atacar(); }
void CommandAtacar::Deshacer() { /* Lógica si se aplica */ }