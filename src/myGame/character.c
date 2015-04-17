#include "common.h"
#include "myGame/wall.h"
#include "myGame/scr.h"

static int trace[GRIDS_X][GRIDS_Y];
/*
  char_x: x--the position of left-up corner
  char_y: y--as above
 */
static int char_x = INI_X , char_y = INI_Y;

int getx() {
    return char_x;
}

int gety() {
    return char_y;
}

void char_reinit() {
    unsigned int i = 0;
    for (; i < GRIDS_X; i++) {
        unsigned int j = 0;
        for (; j < GRIDS_Y; j++) {
            trace[i][j] = 0;
        }
    }
    char_x = INI_X;
    char_y = INI_Y;
}
Dir* surrond() {
    static Dir res[5];
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
    res[i] = NO;
    return res;
}

void assume_move(Dir d, int *x, int *y) {
     switch(d) {
        case UP:
            *x -= 1;
            break;
        case DOWN:
            *x += 1;
            break;
        case LEFT:
            *y -= 1;
            break;
        case RIGHT:
            *y += 1;
            break;
        default:
            assert(0);
            break;
    }
}

void update(Dir d) {
    assume_move(d, &char_x, &char_y);
   //update trace
    printk("dir is %d\n", d);
    trace[char_x][char_y]++;
    //update screen
    set_src_x(char_x);
    set_src_y(char_y);
}

int offset_screen(int cx, int cy) {
    int x = cx - (get_src_x() - XLS);
    int y = cy - (get_src_y() - YLS);
    if (x >= 2 * XLS - 1 || y >= 2 * YLS - 1 || x <= 0 || y <= 0) {
        return -1;
    }
    int res = (x * SCR_WIDTH + y) * MOVE_WIDTH;
    //res += (TO_GRID_CEN * SCR_WIDTH + TO_GRID_CEN);
    //printk("offset is %d\n", res);
    return res;
}

/*
  return: the position to start drawing head bmp
 */
int off_to_screen() {
    check(&char_x, 1, GRIDS_X-1);
    check(&char_y, 1, GRIDS_Y-1);

    return offset_screen(char_x, char_y);
}

