// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"
#include "BloqueAcero.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API ABloqueAcero : public ABloqueBase
{
	GENERATED_BODY()

public:

	ABloqueAcero();
	virtual void InitializeBlock() override;


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
};
