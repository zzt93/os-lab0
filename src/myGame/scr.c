#include "myGame/scr.h"
#include "common.h"
#include "x86/x86.h"

static const int x_limit_s = XLS;
static const int y_limit_s = YLS;
static const int x_limit_l = (GRIDS_X - XLS - 1);
static const int y_limit_l = (GRIDS_Y - YLS);

/*
  scr_x: x--the position of middle of screen
  scr_y: y--as above
 */
static int scr_x = SCR_X;
static int scr_y = SCR_Y;

int get_src_x() {
    return scr_x;
}

int get_src_y() {
    return scr_y;
}

void scr_reinit() {
    scr_x = SCR_X;
    scr_y = SCR_Y;
}

void set_src_x(int x) {
	disable_interrupt();
    scr_x = x;
    check(&scr_x, x_limit_s, x_limit_l);
	enable_interrupt();
}

void set_src_y(int y) {
	disable_interrupt();
    scr_y = y;
    check(&scr_y, y_limit_s, y_limit_l);
	enable_interrupt();
}

void check(int* x, int x_l_s, int x_l_l) {
    if (*x < x_l_s) {
        printk("parameter is :%d smaller than %d\n", *x, x_l_s);
        *x = x_l_s;
    } else if (*x > x_l_l) {
        printk("parameter is :%d larger than %d\n", *x, x_l_l);
        *x = x_l_l;
    }

}

/* size_x : the size relative to move
 */
int to_start() {
    check(&scr_x, x_limit_s, x_limit_l);
    check(&scr_y, y_limit_s, y_limit_l);

    int res = ((scr_x - x_limit_s)*MAZE_W + (scr_y - y_limit_s))*MOVE_WIDTH;
    //res += (TO_GRID_CEN * MAZE_W + TO_GRID_CEN);
    return res;
}