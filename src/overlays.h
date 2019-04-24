#ifndef __OVERLAYS__H_
#define __OVERLAYS__H_

#include <kos.h>
#include <png/png.h>
#include "utilities.h"
#include "textoutput.h"

void overlays_init();

void overlays_renderScore( int score );
void overlays_renderPressToStart();

#endif
