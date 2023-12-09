#define NATIVE_SCRIPT_DLL

#include "NativeScript/NativeScript.h"

#include "Scripts/Player.h"
#include "Scripts/Enemy.h"
#include "Scripts/PlayerCamera.h"
#include "Scripts/PlayerHitbox.h"

extern "C" {
    API_CLASS void RegisterClasses() {
        REGISTER_CLASS(Player)
        REGISTER_CLASS(PlayerCamera)
        REGISTER_CLASS(Enemy)
        REGISTER_CLASS(PlayerHitbox)
    }
}