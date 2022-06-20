/******************************************************************************
*******************************************************************************

	Wreck of the Defiance
	Susseratal
	http://susseratal.me.uk

*******************************************************************************
******************************************************************************/

#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine() // still don't know what ~Engine is going to be needed for and I think it's stupid
{
}

void Engine::initHardware() // sets video modes and VRAM banks 
{
    glBegin2D();
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_SPRITE); // There are 3 VRAM banks for main screen - A,B,C - here I only use A
    vramSetBankD(VRAM_D_SUB_SPRITE); // There are 3 VRAM banks for sub screen - D,H,I - Here i only use D
    // There is an additional F bank for - why didn't i finish this comment?
}

void Engine::Main()
{
    initHardware();

    while(1)
    {
        glBox(2, 10, 10, 2, 101010); // use the 3d rendering core to draw a 2d box
    }
}

/*
void Engine::Main()
{
    initHardware();
    touchPosition touchPos;

    oamInit(&oamMain, SpriteMapping_1D_32, false);
    oamInit(&oamSub, SpriteMapping_1D_32, false);

    u16* gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
    u16* gfxSub = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);

    for(int i = 0; i < 16 * 16 / 2; i++)
    {
        gfx[i] = 1 | (1 << 8);
        gfxSub[i] = 1 | (1 << 8);
    }

    SPRITE_PALETTE[1] = RGB15(0,0,31);
    SPRITE_PALETTE_SUB[1] = RGB15(0,31,0);

    while(1) // constantly spins waiting for something to happen - like event tick
    {
        scanKeys();

        int held = keysHeld();

        if(held & KEY_TOUCH)
        {
            touchRead(&touchPos); // read the touch position
        }

        if(held & KEY_START)
        {
            break;
        }

        // oam = Object Attribute Memory
        oamSet(&oamMain, // main graphics engine context (i don't know what that means)
                0, // oam index (1 - 127) 
                touchPos.px, touchPos.py, // x and y pixel location of the sprite
                0, // proiority, lower renders later - 0 is last and therefore on top
                0, // palette index if multiple palettes or alpha value 
                SpriteSize_16x16, 
                SpriteColorFormat_256Color,
                gfx, // pointer to the loaded graphics
                -1, // sprite rotation data ???
                false, // double the size when rotating - bool
                false, // hide the sprite - bool
                false, false, // vertical flip bool - horizontal flip bool
                false); // apply mosaic - not sure what that is - bool

        oamSet(&oamSub, // sub graphics engine - screen 2
                0, // oam index (1 - 127) 
                touchPos.px, touchPos.py, // x and y pixel location of the sprite
                0, // proiority, lower renders later - 0 is last and therefore on top
                0, // palette index if multiple palettes or alpha value 
                SpriteSize_16x16, 
                SpriteColorFormat_256Color,
                gfx, // pointer to the loaded graphics
                -1, // sprite rotation data ???
                false, // double the size when rotating - bool
                false, // hide the sprite - bool
                false, false, // vertical flip bool - horizontal flip bool
                false); // apply mosaic - not sure what that is - bool

        swiWaitForVBlank(); // ?
        oamUpdate(&oamMain); // update the main screen
        oamUpdate(&oamSub); // update the sub screen
    }
}
*/
