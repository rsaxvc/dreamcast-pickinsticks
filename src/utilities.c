#include "utilities.h"

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
	) {
	
	pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
	
	pvr_poly_cxt_txr(&cxt, displayList, format, texWidth, texHeight, texture, PVR_FILTER_BILINEAR);
	
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);    
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;
    
    vert.x = left;
    vert.y = top;
    vert.z = z;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));
    
    vert.x = right;
    vert.y = top;
    vert.z = z;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));
    
    vert.x = left;
    vert.y = bottom;
    vert.z = z;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));
    
    vert.x = right;
    vert.y = bottom;
    vert.z = z;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

int utilities_isCollision( Rectangle* first, Rectangle* second ) {
	if( first->x + first->w <= second->x ||
		second->x + second->w <= first->x 
		) {
		return 0;
	}
	
	if( first->y + first->h <= second->y ||
		second->y + second->h <= first->y
		) {
		return 0;
	}
	
	return 1;
}

int input_isPressed( int which ) {
	int result = 0;
	
	MAPLE_FOREACH_BEGIN( MAPLE_FUNC_CONTROLLER, cont_state_t, st )
		result = result | ( st->buttons & which );
	MAPLE_FOREACH_END()
	
	return result;
}


void frame_begin() {
	pvr_wait_ready();

	pvr_scene_begin();
	pvr_list_begin( PVR_LIST_TR_POLY );
}

void frame_end() {
	pvr_list_finish();
	pvr_scene_finish();
}
