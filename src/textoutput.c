#include "textoutput.h"

extern char wfont[];

pvr_ptr_t font_tex;

void textoutput_init() {
    int i,x,y,c;
    unsigned short * temp_tex;
    
    font_tex = pvr_mem_malloc(256*256*2);
    temp_tex = (unsigned short *)malloc(256*128*2);
    
    c = 0;
    for(y = 0; y < 128 ; y+=16)
        for(x = 0; x < 256 ; x+=8) {
            for(i = 0; i < 16; i++) {
                temp_tex[x + (y+i) * 256 + 0] = 0xffff * ((wfont[c+i] & 0x80)>>7);
                temp_tex[x + (y+i) * 256 + 1] = 0xffff * ((wfont[c+i] & 0x40)>>6);
                temp_tex[x + (y+i) * 256 + 2] = 0xffff * ((wfont[c+i] & 0x20)>>5);
                temp_tex[x + (y+i) * 256 + 3] = 0xffff * ((wfont[c+i] & 0x10)>>4);
                temp_tex[x + (y+i) * 256 + 4] = 0xffff * ((wfont[c+i] & 0x08)>>3);
                temp_tex[x + (y+i) * 256 + 5] = 0xffff * ((wfont[c+i] & 0x04)>>2);
                temp_tex[x + (y+i) * 256 + 6] = 0xffff * ((wfont[c+i] & 0x02)>>1);
                temp_tex[x + (y+i) * 256 + 7] = 0xffff * (wfont[c+i] & 0x01);
            }
            c+=16;
        }
    pvr_txr_load_ex(temp_tex, font_tex, 256, 256, PVR_TXRLOAD_16BPP);
}

void draw_char(float x1, float y1, float z1, float a, float r, float g, float b, int c, float xs, float ys) {
    pvr_vertex_t    vert;
    int             ix, iy;
    float           u1, v1, u2, v2;
	
    ix = (c % 32) * 8;
    iy = (c / 32) * 16;
    u1 = (ix + 0.5f) * 1.0f / 256.0f;
    v1 = (iy + 0.5f) * 1.0f / 256.0f;
    u2 = (ix+7.5f) * 1.0f / 256.0f;
    v2 = (iy+15.5f) * 1.0f / 256.0f;
    
    vert.flags = PVR_CMD_VERTEX;
    vert.x = x1;
    vert.y = y1 + 16.0f * ys;
    vert.z = z1;
    vert.u = u1;
    vert.v = v2;
    vert.argb = PVR_PACK_COLOR(a,r,g,b);
    vert.oargb = 0;
    pvr_prim(&vert, sizeof(vert));
    
    vert.x = x1;
    vert.y = y1;
    vert.u = u1;
    vert.v = v1;
    pvr_prim(&vert, sizeof(vert));
    
    vert.x = x1 + 8.0f * xs;
    vert.y = y1 + 16.0f * ys;
    vert.u = u2;
    vert.v = v2;
    pvr_prim(&vert, sizeof(vert));
    
    vert.flags = PVR_CMD_VERTEX_EOL;
    vert.x = x1 + 8.0f * xs;
    vert.y = y1;
    vert.u = u2;
    vert.v = v1;
    pvr_prim(&vert, sizeof(vert));
}

void textoutput_print( float x, float y, char *str, TextSize size ) {
  float a = 1.0f;
  float r = 1.0f;
  float g = 1.0f;
  float b = 1.0f;
  
  float xs = size;
  float ys = size;
  
  float z = 2.0f;
  pvr_poly_cxt_t cxt;
  pvr_poly_hdr_t hdr;
  float orig_x = x;

  pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, font_tex, PVR_FILTER_BILINEAR);
  pvr_poly_compile(&hdr, &cxt);
  pvr_prim(&hdr, sizeof(hdr));
  
  while (*str) {
    if (*str == '\n')
    {
      x = orig_x;
      y += 40;
      str++;
      continue;
    }
    draw_char(x, y, z, a, r, g, b, *str++, xs, ys);
	x+=8*xs;
  }
}

void p_itoa( char* s, int number ) {
	char temp[] = "Temporary storage!";
	signed char digits = 0;

	while( number >= 10 ) {
		temp[digits] = '0' + number % 10;
		number = number / 10;
		digits++;
	}

	temp[digits] = '0' + number;

	// copy digits to return string, reversing order
	while(digits >= 0) {
		*s++ = temp[digits];
		digits--;
	}

	// add terminator
	*s = 0;

	// hasta la vista baby!
}

void textoutput_printInteger( float x, float y, int number, TextSize size ) {
	char* buffer = "      ";
	p_itoa( buffer, number );
	textoutput_print( x, y, buffer, size );
}
