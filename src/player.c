#include "player.h"

#define BEAR_TEX_WIDTH 64
#define BEAR_TEX_HEIGHT 128
#define BEAR_WIDTH 64
#define BEAR_HEIGHT 128
#define SPEED 5

#define MIN_X 0
#define MAX_X ( SCREEN_WIDTH - BEAR_WIDTH )
#define MIN_Y 0
#define MAX_Y ( SCREEN_HEIGHT - BEAR_HEIGHT )
#define JUMP_VELOCITY -11.0f

pvr_ptr_t bear_tex;

Rectangle p_box;

void player_reset() {
	p_box.x = SCREEN_WIDTH / 2 - BEAR_WIDTH;
	p_box.y = SCREEN_HEIGHT / 2 - BEAR_HEIGHT;
	p_box.w = BEAR_WIDTH;
	p_box.h = BEAR_HEIGHT;
}

void player_init() {
	bear_tex = pvr_mem_malloc( BEAR_TEX_WIDTH * BEAR_TEX_HEIGHT * 2 );
	png_to_texture("/rd/bear0.png", bear_tex, PNG_FULL_ALPHA);
	player_reset();
}

void player_update() {
	if( input_isPressed( CONT_DPAD_UP ) ) {
		p_box.y -= SPEED;
	}
	if( input_isPressed( CONT_DPAD_DOWN ) ) {
		p_box.y += SPEED;
	}
	if( input_isPressed( CONT_DPAD_LEFT ) ) {
		p_box.x -= SPEED;
	}
	if( input_isPressed( CONT_DPAD_RIGHT ) ) {
		p_box.x += SPEED;
	}

	if( (int)p_box.y > MAX_Y ) {
		p_box.y = MAX_Y;
	}
	if( (int)p_box.x > MAX_X ) {
		p_box.x = MAX_X;
	}
	if( (int)p_box.y < MIN_Y ) {
		p_box.y = MIN_Y;
	}
	if( (int)p_box.x < MIN_X ) {
		p_box.x = MIN_X;
	}
}

void p_drawBear( int x, int y ) {
	draw_polygon( 
		x, 
		y, 
		x + BEAR_WIDTH, 
		y + BEAR_HEIGHT, 
		2, 
		bear_tex,
		BEAR_TEX_WIDTH, 
		BEAR_TEX_HEIGHT, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
}

void player_render() {
	p_drawBear( (int)p_box.x, (int)p_box.y );
}

Rectangle* player_getCollisionBox() {
	return &p_box;
}
