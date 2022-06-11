#include <stdio.h>
#include <stdlib.h>
#include <gl2d.h>
#include <unistd.h>
#include <nds.h>
#include <nds/ndstypes.h>
#include <nds/arm9/video.h>
#include <nds/memory.h>
#include <nds/system.h>

void init()
{
    // PrintConsole* consoleInit(int layer, BgType type, BgSize size, int mapBase, int tileBase, bool mainDisplay, bool loadGraphics); // this takes some arguments so I guess I now get to figure that out lmao
    // consoleDemoInit(); // init the console in demo mode to use iprintf functionality
    // videoSetMode(MODE_5_3D); // allows us to use the 3D rendering tech to render 2d better?
    // glScreen2D(); // init in 2d
    //
}

int main()
{
    // iprintf("\n Hello World!\n"); // this may not work when no longer in demo mode

    touchPosition touchPos;

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

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
    return 0;
}

/*
   ------ old main -----
int main(void) {
	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("      \nHello world!\n");
 
	while(1) {
	
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH 
		iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);		
	
	}

	return 0;
}
*/
