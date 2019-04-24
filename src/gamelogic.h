#ifndef __GAMELOGIC__H_
#define __GAMELOGIC__H_

#include <kos.h>
#include <png/png.h>
#include "utilities.h"

void gamelogic_init();
void gamelogic_reset();

void gamelogic_scroll();
void gamelogic_render();

// provides a one-chance to detect scoring
int gamelogic_hasScored( Rectangle* playerBox );
int gamelogic_hasLost( Rectangle* playerBox );

#endif
