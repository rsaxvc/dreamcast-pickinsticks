#include "gamelogic.h"
#include <stdlib.h>

#define STICK_TEX_WIDTH 32
#define STICK_WIDTH 64

// defines stick spawn points
typedef struct Stick {
	int x;
	int y;
} Stick;

#define NUM_STICKS 17

// keep a bookmark to speed up lookups from linear to constant time
int p_currentStickIndex;
pvr_ptr_t burger_tex;

int p_x;
int p_y;


void place_stick() {
	p_x = rand() % SCREEN_WIDTH;
	p_y = rand() % SCREEN_HEIGHT;
}

void gamelogic_reset() {
	
	place_stick();
}

void gamelogic_init() {
	burger_tex = pvr_mem_malloc( STICK_TEX_WIDTH * STICK_TEX_WIDTH * 2 );
    png_to_texture( "/rd/burger.png", burger_tex, PNG_FULL_ALPHA );
	gamelogic_reset();
}

void p_advanceStick() {
	place_stick();
}

void gamelogic_scroll() {
}

void p_renderStick() {
	draw_polygon( 
		p_x, 
		p_y, 
		STICK_WIDTH + p_x, 
		STICK_WIDTH + p_y, 
		2, 
		burger_tex, 
		STICK_TEX_WIDTH, 
		STICK_TEX_WIDTH, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
}

void gamelogic_render() {
	p_renderStick();
}

// check collision with current burger
int gamelogic_hasScored( Rectangle* playerBox ) {
	Rectangle burgerBox;
	burgerBox.x = p_x;
	burgerBox.y = p_y;
	burgerBox.w = STICK_WIDTH;
	burgerBox.h = STICK_WIDTH;

	if( utilities_isCollision( &burgerBox, playerBox ) )
		{
		p_advanceStick();
		return 1;
		}
	return 0;
}

// check collision with current stick
int gamelogic_hasWon( int score ) {
	return score == 100;
}
