#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

UINTERFACE(Blueprintable)
class UWeaponInterface : public UInterface
{
    GENERATED_BODY()
};

class SHOOTINGGAMEC_API IWeaponInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void PressKey_Shoot();

    virtual void PressKey_Shoot_Implementation() {};

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ReleasedKey_Shoot();

    virtual void ReleasedKey_Shoot_Implementation() {};

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void PressKey_R();

    virtual void PressKey_R_Implementation() {};

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void NotifyShoot();

    virtual void NotifyShoot_Implementation() {};

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void NotifyReload();

    virtual void NotifyReload_Implementation() {};

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharacterEquip(ACharacter* targetChar);

    virtual void OnCharacterEquip_Implementation(ACharacter* targetChar) {};
};