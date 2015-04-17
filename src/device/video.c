#include "common.h"
#include "string.h"
#include "device/video.h"
#include "device/font.h"
#include "device/palette.h"

#include "myGame/scr.h"
#include "myGame/end3_bmp"


/* 绘制屏幕的帧缓冲实现。
 * 在某些版本的qemu-kvm上，由于每次访问显存映射区域都会产生一次VM exit，
 * 更新屏幕的速度可能非常缓慢从而引起游戏跳帧。定义宏SLOW以只重绘屏幕变化
 * 的部分；定义宏TOOSLOW在只重绘屏幕变化部分的基础上，隔行更新。
 * TOOSLOW可能会引起视觉效果的损失。 */
#define SLOW

#ifdef TOOSLOW
	#define PARTIAL_UPDATE
	#define INTERLACE
#else
#ifdef SLOW
	#define PARTIAL_UPDATE
#endif
#endif

uint8_t *vmem = VMEM_ADDR;
static uint8_t vbuf[SCR_SIZE];
#ifdef PARTIAL_UPDATE
static uint8_t vref[SCR_SIZE];
#endif

void
prepare_buffer(void) {
#ifdef PARTIAL_UPDATE
	memcpy(vref, vbuf, SCR_SIZE);
#endif
	vmem = vbuf;//in order make draw_string write to buffer
	//memset(vbuf, 0, SCR_SIZE);// this line make it all blank
    draw_picture(end3_bmp + to_start(), MAZE_W, MAZE_H, 0);
}

void
display_buffer(void) {
#ifdef PARTIAL_UPDATE
	int i;
#ifdef INTERLACE
	static int update_line = 0;
	update_line ^= 1;
#endif
	uint32_t *buf = (uint32_t*)vbuf;
	uint32_t *ref = (uint32_t*)vref;
	uint32_t *mem = (uint32_t*)VMEM_ADDR;
	vmem = VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i ++) {
#ifdef INTERLACE
		if ((i * 4 / SCR_WIDTH) % 2 == update_line) {
			buf[i] = ref[i];
			continue;
		}
#endif
		if (buf[i] != ref[i]) {
			mem[i] = buf[i];
		}
	}
#else
	vmem = VMEM_ADDR;
	asm volatile ("cld; rep movsl" : : "c"(SCR_SIZE / 4), "S"(vbuf), "D"(vmem));
#endif
}

static inline void
draw_character(char ch, int x, int y, int color) {
	int i, j;
	assert((ch & 0x80) == 0);
	char *p = font8x8_basic[(int)ch];
	for (i = 0; i < 8; i ++)
		for (j = 0; j < 8; j ++)
			if ((p[i] >> j) & 1)
				draw_pixel(x + i, y + j, color);
}

void
draw_string(const char *str, int x, int y, int color) {
	while (*str) {
		draw_character(*str ++, x, y, color);
		if (y + 8 >= SCR_WIDTH) {
			x += 8; y = 0;
		} else {
			y += 8;
		}
	}
}

void draw_picture(unsigned char *s, int w, int h, int des_off) {
    unsigned int i = 0;
    unsigned char *buf = vbuf + des_off;
    h = (h > SCR_HEIGHT) ? SCR_HEIGHT : h;
    int tmp = (w > SCR_WIDTH) ? SCR_WIDTH : w;
    for (i = 0; i < h; i++) {
        memcpy(buf + i*SCR_WIDTH, s + i*w, tmp);
    }
}


bool isWhite(int i) {
    int in = end3_bmp[i];
    P color = getColor(in);
    if (color.r >= 0xd0 && color.g >= 0xd0 && color.b >= 0xd0) {
        return TRUE;
    }
    return FALSE;
}

void set_color(int des_off, unsigned char color, int len) {
    memset(vbuf + des_off, color, len);
}


/*
  args: {now: the offset relative to the start of screen}
  return value:
  Usage: draw the 9 pixels
*/

#define R 3
void draw_point(int now, unsigned char color) {
    int first = now - SCR_WIDTH - 1;
    int last = now + SCR_WIDTH + 1;
    unsigned char * buf = vbuf + now;
    //printk("first %d last %d\n", first, last);
    assert(first >= 0 && last < SCR_SIZE);
    unsigned int i;
    for (i = 0; i < R; ++i) {
        memset(buf + i*SCR_WIDTH, color, R);
    }
}