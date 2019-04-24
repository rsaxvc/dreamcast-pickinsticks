#ifndef __TEST_OUTPUT__H_
#define __TEST_OUTPUT__H_

#include <kos.h>

typedef enum TextSize {
	SMALL = 1,
	LARGE = 2
} TextSize;

void textoutput_init();
void textoutput_print( float x, float y, char *str, TextSize size );
void textoutput_printInteger( float x, float y, int number, TextSize size );

#endif
