#ifndef __UTILITIES__H_
#define __UTILITIES__H_

#include <kos.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct Rectangle {
	int x, y;
	int w, h;
} Rectangle;

int utilities_isCollision( Rectangle* first, Rectangle* second );

void draw_polygon( 
	int left, 
	int top, 
	int right, 
	int bottom, 
	int z,
	pvr_ptr_t texture, 
	int texWidth, 
	int texHeight,
	pvr_list_t displayList,
	int format
	);

int input_isPressed( int which );

void frame_begin();
void frame_end();
	
#endif
