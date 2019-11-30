#include "scrollingbackground.h"

#define LAYER_TEX_HEIGHT 256
#define LAYER_TEX_WIDTH 1024
#define LAYER_WIDTH 1920
#define LAYER_HEIGHT ( LAYER_WIDTH * LAYER_TEX_HEIGHT ) / LAYER_TEX_WIDTH

#define FRONT_TEX_HEIGHT 128
#define FRONT_TEX_WIDTH 1024
#define FRONT_WIDTH 800
#define FRONT_HEIGHT 1 * ( ( FRONT_WIDTH * FRONT_TEX_HEIGHT ) / FRONT_TEX_WIDTH )

pvr_ptr_t back_tex;

long p_backgroundX;
long p_frontLayerX;

void scrollingbackground_reset() {
	p_backgroundX = 0;
	p_frontLayerX = 0;
}

void scrollingbackground_init() {
    back_tex = pvr_mem_malloc( LAYER_TEX_WIDTH * LAYER_TEX_HEIGHT * 2 );
    png_to_texture("/rd/background.png", back_tex, PNG_NO_ALPHA);

	scrollingbackground_reset();
}

void scrollingbackground_scroll() {
	p_backgroundX -= 3;
	
	if( p_backgroundX < -1 * LAYER_WIDTH ) {
		p_backgroundX += LAYER_WIDTH;
	}
	
	p_frontLayerX -= 6;
	
	if( p_frontLayerX < -1 * FRONT_WIDTH ) {
		p_frontLayerX += FRONT_WIDTH;
	}
}

void p_drawBackground( int x ) {
	draw_polygon( 
		x, 
		0, 
		LAYER_WIDTH + x, 
		LAYER_HEIGHT, 
		1, 
		back_tex, 
		LAYER_TEX_WIDTH, 
		LAYER_TEX_HEIGHT, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_RGB565 
		);
}

void scrollingbackground_render() {
	p_drawBackground( p_backgroundX );
	p_drawBackground( p_backgroundX + LAYER_WIDTH );
}
