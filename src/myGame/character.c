#include "common.h"
#include "myGame/wall.h"
#include "myGame/scr.h"

static int trace[GRIDS_X][GRIDS_Y];
static int char_x = INI_X , char_y = INI_Y;

int getx() {
    return char_x;
}

int gety() {
    return char_y;
}

Dir* surrond() {
    static Dir res[4];
    int i = 0;
    if (char_x == 0) {
        res[i++] = RIGHT;
    } else if (char_x < GRIDS_X - 1) {
        res[i++] = LEFT;
        res[i++] = RIGHT;
    } else {
        res[i++] = LEFT;
    }
    if (char_y == 0) {
        res[i++] = DOWN;
    } else if (char_y < GRIDS_Y - 1) {
        res[i++] = DOWN;
        res[i++] = UP;
    } else {
        res[i++] = UP;
    }
    return res;
}

void assume_move(Dir d, int *x, int *y) {
     switch(d) {
        case UP:
            *y -= 1;
            break;
        case DOWN:
            *y += 1;
            break;
        case LEFT:
            *x -= 1;
            break;
        case RIGHT:
            *x += 1;
            break;
        default:
            assert(0);
            break;
    }
}

void update(Dir d, int *x, int *y) {
    assume_move(d, x, y);
   //update trace
    trace[*x][*y]++;
}

int off_to_screen() {
    check(char_x, 1, GRIDS_X-1);
    check(char_x, 1, GRIDS_Y-1);

    int x = char_x - (get_src_x() - XLS);
    int y = char_y - (get_src_y() - YLS);
    int res = (x * SCR_WIDTH + y) * MOVE_WIDTH;
    //printk("offset is %d\n", res);
    return res;
}