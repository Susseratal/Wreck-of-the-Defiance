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

#include "gl2d.h"

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