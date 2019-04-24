#include "gamelogic.h"

#define BURGER_TEX_WIDTH 32
#define BURGER_WIDTH 64
#define ROCK_TEX_WIDTH 128
#define ROCK_BOTTOM_Y (SCREEN_HEIGHT - 20)

// defines burger spawn points
typedef struct Burger {
	int x;
	int y;
} Burger;

// defines rock spawn points and sizes
typedef struct Rock {
	int x;
	int sideLength;
} Rock;

#define NUM_BURGERS 17
Burger p_burgers[] = { 
	{ 700, 200 }, { 1500, 120 }, { 2200, 150 }, { 3200, 100 }, { 4100, 130 } ,
	{ 5800, 300 }, { 6500, 100 }, { 7600, 310 }, { 8300, 150 }, { 8940, 100 } ,
	{ 9600, 320 }, { 11000, 380 }, { 13000, 100 }, { 14000, 120 }, { 15000, 180 }, 
	{ 15900, 320 }, { 999999, 320 }
};

// keep a bookmark to speed up lookups from linear to constant time
int p_currentBurgerIndex;
int p_lastEatenBurgerIndex;
pvr_ptr_t burger_tex;

#define NUM_ROCKS 17
Rock p_rocks[] = { 
	{ 1500, 80 }, { 2200, 100 }, { 3500, 120 }, { 4200, 80 }, { 4900, 50 }, 
	{ 5900, 130 }, { 6600, 60 }, { 7500, 70 }, { 8600, 100 }, { 9270, 90 }, 
	{ 10000, 120 }, { 10940, 90 }, { 12900, 130 }, { 13800, 70 }, { 15000, 70 }, 
	{ 16600, 300 }, { 999999, 20 }
};
int p_currentRockIndex;
pvr_ptr_t rock_tex;

int p_scrollX;
long p_frames;
int p_missedBurger;

void gamelogic_reset() {
	p_scrollX = 0;
	
	p_currentBurgerIndex = 0;
	p_currentRockIndex = 0;
	p_frames = 0;
	p_lastEatenBurgerIndex = -1;
	p_missedBurger = 0;
}

void gamelogic_init() {
	burger_tex = pvr_mem_malloc( BURGER_TEX_WIDTH * BURGER_TEX_WIDTH * 2 );
    png_to_texture( "/rd/burger.png", burger_tex, PNG_FULL_ALPHA );
	
	rock_tex = pvr_mem_malloc( ROCK_TEX_WIDTH * ROCK_TEX_WIDTH * 2 );
    png_to_texture( "/rd/rock.png", rock_tex, PNG_FULL_ALPHA );
	
	gamelogic_reset();
}

void p_advanceBurger() {
	if( p_currentBurgerIndex >= NUM_BURGERS ) {
		return;
	}
	
	// has current burger scrolled off-screen to the left?
	int currentBurgerRightEdgeX = p_burgers[ p_currentBurgerIndex ].x + BURGER_WIDTH;
	if( currentBurgerRightEdgeX < p_scrollX ) {
		p_missedBurger = p_lastEatenBurgerIndex != p_currentBurgerIndex;
		p_currentBurgerIndex++;
	}
}

void p_advanceRock() {
	if( p_currentRockIndex >= NUM_ROCKS ) {
		return;
	}
	
	// has current rock scrolled off-screen to the left?
	int currentRockRightEdgeX = p_rocks[ p_currentRockIndex ].x + p_rocks[ p_currentRockIndex ].sideLength;
	if( currentRockRightEdgeX < p_scrollX ) {
		p_currentRockIndex++;
	}
}


void gamelogic_scroll() {
	p_scrollX += 5;
	p_advanceBurger();
	p_advanceRock();
}

void p_renderBurger() {
	if( p_currentBurgerIndex >= NUM_BURGERS ) {
		return;
	}
	
	// was this burger already eaten?
	if( p_currentBurgerIndex == p_lastEatenBurgerIndex ) {
		return;
	}
	
	// adjust for scroll
	int x = p_burgers[ p_currentBurgerIndex ].x - p_scrollX;
	int y = p_burgers[ p_currentBurgerIndex ].y;
	
	// bounce burger up and down
	if( p_frames % 10 < 5 ) {
		y += 5;
	}
	
	draw_polygon( 
		x, 
		y, 
		BURGER_WIDTH + x, 
		BURGER_WIDTH + y, 
		2, 
		burger_tex, 
		BURGER_TEX_WIDTH, 
		BURGER_TEX_WIDTH, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
}

void p_renderRock() {
	if( p_currentRockIndex >= NUM_ROCKS ) {
		return;
	}
	
	// adjust for scroll
	int size = p_rocks[ p_currentRockIndex ].sideLength;
	int x = p_rocks[ p_currentRockIndex ].x - p_scrollX;
	int y = ROCK_BOTTOM_Y - size;
	
	draw_polygon( 
		x, 
		y, 
		x + size, 
		y + size, 
		2, 
		rock_tex, 
		ROCK_TEX_WIDTH, 
		ROCK_TEX_WIDTH, 
		PVR_LIST_TR_POLY, 
		PVR_TXRFMT_ARGB4444
		);
}

void gamelogic_render() {
	p_frames++;	
	p_renderBurger();
	p_renderRock();
}

// check collision with current burger
int gamelogic_hasScored( Rectangle* playerBox ) {
	if( p_currentBurgerIndex >= NUM_BURGERS ) {
		return 0;
	}
	
	// was this burger already eaten?
	if( p_currentBurgerIndex == p_lastEatenBurgerIndex ) {
		return 0;
	}
	
	Rectangle burgerBox;
	burgerBox.x = p_burgers[ p_currentBurgerIndex ].x - p_scrollX;
	burgerBox.y = p_burgers[ p_currentBurgerIndex ].y;
	burgerBox.w = BURGER_WIDTH;
	burgerBox.h = BURGER_WIDTH;
	
	int isCollision = utilities_isCollision( &burgerBox, playerBox );
	
	if( isCollision ) {
		p_lastEatenBurgerIndex = p_currentBurgerIndex;
	}
	
	return isCollision;
}

// check collision with current obstacle and whether a burger was missed
int gamelogic_hasLost( Rectangle* playerBox ) {
	if( p_currentRockIndex >= NUM_ROCKS ) {
		return 0;
	}
	
	Rectangle rockBox;
	rockBox.w = p_rocks[ p_currentRockIndex ].sideLength;
	rockBox.h = p_rocks[ p_currentRockIndex ].sideLength;
	rockBox.x = p_rocks[ p_currentRockIndex ].x - p_scrollX;
	rockBox.y = ROCK_BOTTOM_Y - rockBox.h;
	
	int isCollision = utilities_isCollision( &rockBox, playerBox );
	
	return isCollision || p_missedBurger;
}
