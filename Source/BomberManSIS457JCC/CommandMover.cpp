// Fill out your copyright notice in the Description page of Project Settings.
#include "CommandMover.h"
#include "EnemigoBase.h"

CommandMover::CommandMover(AEnemigoBase* InReceptor) : Receptor(InReceptor) {}

void CommandMover::Ejecutar() { if (Receptor) Receptor->Moverse(); }
void CommandMover::Deshacer() { /* Si quieres, puedes implementar lógica para deshacer el movimiento */ }