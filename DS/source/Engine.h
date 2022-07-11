/******************************************************************************
*******************************************************************************

	Wreck of the Defiance
	Susseratal
	http://susseratal.me.uk

*******************************************************************************
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <nds.h>
#include <nds/arm9/videoGL.h>

#include "gl2d.h"
// #include "ndstypes.h"
#include "Memoryfeedback.h"
#include "GlobalManager.h"

#ifndef ENGINE_H // if undefined? 
#define ENGINE_H // def engine

class Engine
{
public:
    Engine();
    ~Engine(); // ???
    void Main();

private:
    void initHardware();
};

#endif // ENGINE_H // again ??!
