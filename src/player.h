#ifndef __PLAYER__H_
#define __PLAYER__H_

#include <kos.h>
#include <png/png.h>
#include "utilities.h"

void player_init();
void player_reset();

void player_render();
void player_update();

void player_jump();
Rectangle* player_getCollisionBox();

#endif
