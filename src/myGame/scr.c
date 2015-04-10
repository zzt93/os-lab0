#include "myGame/scr.h"
#include "common.h"

static const int x_limit_s = XLS;
static const int y_limit_s = YLS;
static const int x_limit_l = (GRIDS_X - XLS);
static const int y_limit_l = (GRIDS_Y - YLS);

static int scr_x = SCR_X;
static int scr_y = SCR_Y;

int get_src_x() {
    return scr_x;
}

int get_src_y() {
    return scr_y;
}

void set_src_x(int x) {
    scr_x = x;
    check(x, x_limit_s, x_limit_l);
}

void set_src_y(int y) {
    scr_y = y;
    check(y, y_limit_s, y_limit_l);
}

void check(int x, int x_l_s, int x_l_l) {
    if (x < x_l_s) {
        printk("x of screen is :%d\n", x);
        x = x_l_s;
    } else if (x > x_l_l) {
        printk("x of screen is :%d\n", x);
        x = x_l_l;
    }

}

/* size_x : the size relative to move
 */
int to_start() {
    check(scr_x, x_limit_s, x_limit_l);
    check(scr_y, y_limit_s, y_limit_l);

    int res = ((scr_x - x_limit_s)*MAZE_W + (scr_y - y_limit_s))*MOVE_WIDTH;
    return res;
}