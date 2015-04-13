#ifndef __WALL_H__
#define __WALL_H__

#include "myGame/maze_const.h"

typedef enum D {
    UP, DOWN, LEFT, RIGHT, NO,
} Dir;

extern bool wall[][GRIDS_Y];

bool can_move(int dir);
#endif /* __WALL_H__ */