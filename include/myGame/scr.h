#ifndef __SCR_H__
#define __SCR_H__

#include "wall.h"

int get_src_x();
int get_src_y();

void set_src_x(int);
void set_src_y(int);

int to_start();
void check(int*, int, int);

#define XLS (SCR_HEIGHT / 2 / MOVE_WIDTH)
#define YLS (SCR_WIDTH/ 2 / MOVE_WIDTH)


#endif /* __SCR_H__ */