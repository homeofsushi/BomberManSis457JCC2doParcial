#include "CommandAtacar.h"
#include "EnemigoBase.h"

CommandAtacar::CommandAtacar(AEnemigoBase* InReceptor) : Receptor(InReceptor) {}

void CommandAtacar::Ejecutar() { if (Receptor) Receptor->Atacar(); }
void CommandAtacar::Deshacer() { /* L�gica si se aplica */ }