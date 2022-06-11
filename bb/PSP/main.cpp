#include <pspkernel.h>
#include <pspdebug.h>
#include <fstream>
#include <iostream>
#include <string>

PSP_MODULE_INFO("Bloodborne", 0, 1, 0);

int exitCallback(int arg1, int arg2, void* common)
{
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp)
{
        int cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
        sceKernelRegisterExitCallback(cbid);

        sceKernelSleepThreadCB();
        return 0;
}

void setupCallbacks()
{
        int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
        if(thid >= 0)
        {
                sceKernelStartThread(thid, 0, NULL);
        }
}

auto main() -> int
{
        setupCallbacks();
        pspDebugScreenInit();
        pspDebugScreenPrintf("ha ha i wish lmao");
}
