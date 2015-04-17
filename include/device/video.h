#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "types.h"
#include "const.h"
#include "assert.h"

#define SCR_WIDTH  320
#define SCR_HEIGHT 200
#define SCR_SIZE ((SCR_WIDTH) * (SCR_HEIGHT))
#define VMEM_ADDR  ((uint8_t*)0xA0000)

extern uint8_t *vmem;

static inline void
draw_pixel(int x, int y, int color) {
	assert(x >= 0 && y >= 0 && x < SCR_HEIGHT && y < SCR_WIDTH);
	vmem[(x << 8) + (x << 6) + y] = color;
}

void prepare_buffer(void);
void display_buffer(void);

void draw_picture(unsigned char*s, int w, int h, int des_off);

void draw_string(const char*, int, int, int);

bool isWhite(int x);
void set_color(int des_off, unsigned char, int len);
void draw_point(int now, unsigned char color);
// pixels of picture
#define HEAD_H 21
#define HEAD_W 23
#define MAZE_H 1024
#define MAZE_W 1024

#define WHITE 0
#define RED 8

#endif
