// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class ICommand
{
public:
    virtual void Ejecutar() = 0;
    virtual void Deshacer() = 0;
};
