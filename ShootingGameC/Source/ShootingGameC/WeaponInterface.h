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
    /** 이 오브젝트를 활성화시키는 트리거 볼륨에 반응합니다. 반응에 성공하면 true 를 반환합니다. */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void PressKey_F();

    virtual void PressKey_F_Implementation(){};
};