#ifndef __PALETTE_H__
#define __PALETTE_H__

typedef struct {
	uint8_t r, g, b, a;
} P;

void write_palette();
void read_palette();

P getColor(int);
#endif
