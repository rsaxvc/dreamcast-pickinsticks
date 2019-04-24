#include "player.h"

#define NUM_BEAR_TEXTURES 5
#define BEAR_TEX_WIDTH 64
#define BEAR_TEX_HEIGHT 128
#define NUM_BEAR_ANIMATION_FRAMES 8
#define BEAR_WIDTH 64
#define BEAR_HEIGHT 128
#define VIDEO_FRAMES_PER_ANIMATION_FRAME 8

#define X_POSITION 80
#define ACCELERATION 0.33f
#define MAXIMUM_Y (SCREEN_HEIGHT - BEAR_HEIGHT - 20)
#define JUMP_VELOCITY -11.0f

pvr_ptr_t bear_tex[NUM_BEAR_TEXTURES];
int p_animationFramesTextureIndices[NUM_BEAR_ANIMATION_FRAMES] = {
	0, 1, 2, 3, 4, 3, 2, 1
};

int p_currentFrame;
long p_videoFrame;

float p_downwardVelocity;
float p_bearY;

Rectangle p_box;
Rectangle p_collisionBox;

void player_reset() {
	p_currentFrame = 0;
	p_videoFrame = 0;
	p_downwardVelocity = 0.0f;
	p_bearY = MAXIMUM_Y;
	
	p_box.x = X_POSITION;
	p_box.w = BEAR_WIDTH;
	p_box.h = BEAR_HEIGHT;
}

void player_init() {
	int i;
	
	for( i = 0; i < NUM_BEAR_TEXTURES; i++ ) {
		bear_tex[i] = pvr_mem_malloc( BEAR_TEX_WIDTH * BEAR_TEX_HEIGHT * 2 );
	}

	png_to_texture("/rd/bear0.png", bear_tex[0], PNG_FULL_ALPHA);
	png_to_texture("/rd/bear1.png", bear_tex[1], PNG_FULL_ALPHA);
	png_to_texture("/rd/bear2.png", bear_tex[2], PNG_FULL_ALPHA);
	png_to_texture("/rd/bear3.png", bear_tex[3], PNG_FULL_ALPHA);
	png_to_texture("/rd/bear4.png", bear_tex[4], PNG_FULL_ALPHA);
	
	player_reset();
}

void player_update() {
	p_videoFrame++;
	
	// advance animation frame
	if( p_videoFrame % VIDEO_FRAMES_PER_ANIMATION_FRAME == 0 ) {
		p_currentFrame = ( p_currentFrame + 1 ) % NUM_BEAR_ANIMATION_FRAMES;
	}
	
	// apply acceleration to velocity
	p_downwardVelocity += ACCELERATION;
	
	p_bearY += p_downwardVelocity;
	
	// the bear lands
	if( (int)p_bearY > MAXIMUM_Y ) {
		p_bearY = MAXIMUM_Y;
		p_downwardVelocity = 0.0f;
	}
	
	p_box.y = (int)p_bearY;
}

void p_drawBear( int x, int y ) {
	draw_polygon( 
		x, 
		y, 
		x + BEAR_WIDTH, 
		y + BEAR_HEIGHT, 
		2, 
		bear_tex[ p_animationFramesTextureIndices[p_currentFrame] ],
		BEAR_TEX_WIDTH, 
		BEAR_TEX_HEIGHT, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
}

void player_render() {
	p_drawBear( X_POSITION, (int)p_bearY );
}

void player_jump() {
	// do nothing if the bear is airborne
	if( p_bearY < MAXIMUM_Y ) {
		return;
	}
	
	p_downwardVelocity = JUMP_VELOCITY;
}

Rectangle* player_getCollisionBox() {
	p_collisionBox.x = p_box.x;
	p_collisionBox.y = p_box.y;
	p_collisionBox.w = p_box.w;
	p_collisionBox.h = p_box.h - 20;
	
	return &p_collisionBox;
}
