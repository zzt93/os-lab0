#include "myGame/character.h"
#include "common.h"
#include "device/video.h"

bool wall[GRIDS_X][GRIDS_Y];

bool has_wall(Dir d, int x, int y) {
    int tmpx = x;
    int tmpy = y;
    assume_move(d, &tmpx, &tmpy);
    int i = (x * MAZE_W + y)*MOVE_WIDTH ;
    i += (TO_GRID_CEN * MAZE_W + MAZE_H);
    // TODO temprorily use HEAD_H/_W /4
    switch(d) {
        case UP:
            i -= (HEAD_H / 4 * MAZE_W);
            break;
        case DOWN:
            i += (HEAD_H / 4 * MAZE_W);
            break;
        case LEFT:
            i -= (HEAD_W / 4);
            break;
        case RIGHT:
            i += (HEAD_W / 4);
            break;
        default:
            assert(0);
            break;
    }
    if (!isWhite(i)) {
        return TRUE;
    }
    //printk("has wall: false\n");
    return FALSE;
}

bool can_move(int dir) {
    Dir* dirs = surrond();
    int last_x = getx();
    int last_y = gety();
    unsigned int i = 0;
    for (i = 0; dirs[i] != NO; i++) {
        //printk("can move dirs[i] %d, dir %d\n", dirs[i], dir);
        if (dirs[i] == dir) {
            if (!has_wall(dirs[i] ,last_x, last_y)) {
                //if can move update last_x, last_y
                update(dirs[i]);
                return TRUE;
            }
        }
    }
    return FALSE;
}
