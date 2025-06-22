// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomba.generated.h"
UENUM(BlueprintType)
enum class EBombType : uint8
{
	Simple    UMETA(DisplayName = "Simple"),
	Creciente UMETA(DisplayName = "Creciente"),
	Textura   UMETA(DisplayName = "Textura")
};



UCLASS()
class BOMBERMANSIS457JCC_API ABomba : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomba();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomba")
	int32 Danio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomba")
	float RadioExplosion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


