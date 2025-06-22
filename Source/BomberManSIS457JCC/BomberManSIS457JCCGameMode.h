// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JuegoFacadeActor.h"
#include "BomberManSIS457JCCGameMode.generated.h"

UCLASS(minimalapi)
class ABomberManSIS457JCCGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	ABomberManSIS457JCCGameMode();
	void SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation);

private:
	AJuegoFacadeActor* Facade;
};



