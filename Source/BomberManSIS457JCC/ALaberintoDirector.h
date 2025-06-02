// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ULaberintoBuilderDefault.h"
#include "ALaberintoDirector.generated.h"

UCLASS()
class BOMBERMANSIS457JCC_API AALaberintoDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AALaberintoDirector();

	void ConstruirLaberinto(class ULaberintoBuilder* Builder);

private:
	UPROPERTY()
	ULaberintoBuilderDefault* Builder; // Guarda referencia si lo necesitas

	UPROPERTY()
	AALaberinto* LaberintoConstruido; // Guarda el laberinto generado

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
