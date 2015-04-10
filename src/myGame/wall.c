#include "myGame/character.h"
#include "device/video.h"

bool wall[GRIDS_X][GRIDS_Y];

bool has_wall(Dir d, int x, int y) {
    int tmpx = x;
    int tmpy = y;
    assume_move(d, &tmpx, &tmpy);
    if (!isWhite(tmpx, tmpy)) {
        return TRUE;
    }
    return FALSE;
}

bool can_move(int dir) {
    Dir* dirs = surrond();
    int last_x = getx();
    int last_y = gety();
    unsigned int i = 0;
    for (i = 0; dirs[i] != NO; i++) {
        if (dirs[i] == dir) {
            if (!has_wall(dirs[i] ,last_x, last_y)) {
                //if can move update last_x, last_y
                update(dirs[i], &last_x, &last_y);
                return TRUE;
            }
        }
    }
    return FALSE;
}
