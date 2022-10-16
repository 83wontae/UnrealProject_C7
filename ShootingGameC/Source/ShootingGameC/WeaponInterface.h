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
    /** �� ������Ʈ�� Ȱ��ȭ��Ű�� Ʈ���� ������ �����մϴ�. ������ �����ϸ� true �� ��ȯ�մϴ�. */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void PressKey_F();

    virtual void PressKey_F_Implementation(){};
};