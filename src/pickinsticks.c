/*
 *
 *    Pickin Sticks
 *             by RSAXVC, 2019
 *             http://rsaxvc.net
 *    BASED ON:
 *    Overbearing Burgers
 *             by Sebastian Mihai, 2015
 *             http://sebastianmihai.com
 *
 */

#include <kos.h>

#include "textoutput.h"
#include "utilities.h"
#include "scrollingbackground.h"
#include "gamelogic.h"
#include "player.h"
#include "overlays.h"

#define LOST_DELAY_FRAMES 100

extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK( romdisk_boot );

int p_score;
int p_eatBurgerSoundHandle;
int p_lostDelay;

void phase_gameplay() {
	while( 1 ) {
		// rendering
		frame_begin();

		scrollingbackground_render();
		gamelogic_render();
		player_render();
		overlays_renderScore( p_score );

		frame_end();

		if( p_lostDelay == 0 ) {
			return;
		}

		if( p_lostDelay < LOST_DELAY_FRAMES ) {
			p_lostDelay--;
			continue;
		}

		// updates
		scrollingbackground_scroll();
		gamelogic_scroll();
		player_update();

		int hasScored = gamelogic_hasScored( player_getCollisionBox() );
		if( hasScored ) {
			p_score++;
		}

		// check for completion
		int hasWon = gamelogic_hasWon( p_score );
		if( hasWon ) {
			p_lostDelay--;
		}
    }
}

void phase_waitToStart() {
	while( 1 ) {
		// rendering
		frame_begin();

		scrollingbackground_render();
		overlays_renderScore( p_score );
		overlays_renderPressToStart();

		frame_end();

		// check for completion
		if( input_isPressed( CONT_START ) ) {
			return;
		}
    }
}

void reset() {
	scrollingbackground_reset();
	gamelogic_reset();
	player_reset();

	p_score = 0;
	p_lostDelay = LOST_DELAY_FRAMES;
}

void initialize() {
	pvr_init_defaults();

    textoutput_init();
	scrollingbackground_init();
	gamelogic_init();
	player_init();
	overlays_init();

	reset();
}

// entry point
int main() {
	initialize();

    while( 1 ) {
		phase_waitToStart();
		reset();
		phase_gameplay();
	}

    return 0;
}
