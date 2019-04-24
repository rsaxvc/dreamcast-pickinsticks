#include "overlays.h"

#define OVERLAY_TEX_WIDTH 128
#define OVERLAY_TEX_HEIGHT 32

#define SCORE_X 50
#define SCORE_Y 35
#define SCORE_WIDTH 160
#define SCORE_HEIGHT ( SCORE_WIDTH / 4 )

#define PRESS_TO_START_WIDTH ( SCREEN_WIDTH - 100 )
#define PRESS_TO_START_HEIGHT ( PRESS_TO_START_WIDTH / 4 )

pvr_ptr_t overlay_tex;

void overlays_init() {
	overlay_tex = pvr_mem_malloc( OVERLAY_TEX_WIDTH * OVERLAY_TEX_HEIGHT * 2 );
	png_to_texture( "/rd/overlay.png", overlay_tex, PNG_FULL_ALPHA );
}

void p_renderAuthor() {
	textoutput_print( 
		SCORE_X + 9,  
		SCORE_Y - 17, 
		"by Sebastian Mihai", 
		SMALL
		);
}

void overlays_renderScore( int score ) {
	draw_polygon( 
		SCORE_X, 
		SCORE_Y, 
		SCORE_X + SCORE_WIDTH, 
		SCORE_Y + SCORE_HEIGHT, 
		2, 
		overlay_tex, 
		OVERLAY_TEX_WIDTH, 
		OVERLAY_TEX_HEIGHT, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
	
	textoutput_print( SCORE_X + 13, SCORE_Y + 4, "score", LARGE );
	textoutput_printInteger( SCORE_X + 115, SCORE_Y + 6, score, LARGE );
	
	p_renderAuthor();
}

void overlays_renderPressToStart() {
	int x = SCREEN_WIDTH / 2 - PRESS_TO_START_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2 - PRESS_TO_START_HEIGHT / 2;
	
	draw_polygon( 
		x, 
		y, 
		x + PRESS_TO_START_WIDTH, 
		y + PRESS_TO_START_HEIGHT, 
		2, 
		overlay_tex, 
		OVERLAY_TEX_WIDTH, 
		OVERLAY_TEX_HEIGHT, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
	
	textoutput_print( 
		x + 65,  
		y + PRESS_TO_START_HEIGHT / 2 - 14, 
		"press START to begin game", 
		LARGE 
		);
		
	p_renderAuthor();
}
