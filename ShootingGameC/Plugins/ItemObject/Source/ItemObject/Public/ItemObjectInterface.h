// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UItemObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITEMOBJECT_API IItemObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AddHealth(float Heal);

	virtual void AddHealth_Implementation(float Heal) {};
};
