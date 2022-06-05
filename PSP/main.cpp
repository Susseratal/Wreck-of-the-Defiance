#include <pspkernel.h>
#include <pspdebug.h>
#include <fstream>
#include <iostream>
#include <string>

PSP_MODULE_INFO("RPG", 0, 1, 0);

int exit_callback(int arg1, int arg2, void* common)
{
        sceKernelExitGame();
        return 0;
}

int callbackThread(SceSize args, void* argp)
{
        int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
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

        std::ofstream file("test.txt"); // create an output file
        file << "hot men from inside my psp" << std::endl;
        file.close();

        std::ifstream file2("test.txt"); // create an input file to read from
        std::string str; // create a string object
        std::getline(file2, str);
        file2.close();

        pspDebugScreenInit();
        pspDebugScreenPrintf(str.c_str());
}
