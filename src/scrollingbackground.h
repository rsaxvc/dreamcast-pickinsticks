#ifndef __SCROLLING_BACKGROUND__H_
#define __SCROLLING_BACKGROUND__H_

#include <kos.h>
#include <png/png.h>
#include "utilities.h"

void scrollingbackground_init();
void scrollingbackground_reset();

void scrollingbackground_render();
void scrollingbackground_scroll();

#endif
