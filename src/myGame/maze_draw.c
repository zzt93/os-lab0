#include "myGame/myGame.h"
#include "string.h"
#include "device/video.h"
#include "myGame/character.h"

#include "myGame/head_bmp"

#define FONT_H 10

static const char* reminder[3] = {"If you want to try again\n,", "press 'enter'\n,", "or press 'esc' to quit."};
#define SIZE_RIM (sizeof reminder / sizeof reminder[0])

void draw_end(Result res) {
    prepare_buffer();
    // draw a blank area
    // can not understand why this need SCR_WIDTH/3 more
    // SOLVED : SCR_SIZE/3 = 21333 % 320 = 213, so need SCR_WIDTH/3 more
    int des_off = SCR_SIZE/3 + SCR_WIDTH/3 + SCR_WIDTH/6;
    unsigned int i;
    for (i = 0; i < SCR_HEIGHT/2; ++i) {
        set_color(des_off + i*SCR_WIDTH, WHITE, 2*SCR_WIDTH/3);
    }

    if (res == WIN) {
        static const char * win = "You WIN";
        draw_string(win, SCR_HEIGHT/2, SCR_WIDTH/2 - strlen(win)/2 * 8, 0x8);
    } else {
        assert (res == LOSE);
        static const char * lose = "You LOSE";
        draw_string(lose, SCR_HEIGHT/2, SCR_WIDTH/2 - strlen(lose)/2 * 8, 0x8);
    }
    for (i = 0; i < SIZE_RIM; ++i) {
        //printk("%d\n", strlen(reminder[i]));
        //printk("screen %d\n", SCR_WIDTH/2);
        draw_string(reminder[i], SCR_HEIGHT/2 + (i + 2) * FONT_H, SCR_WIDTH/2 - strlen(reminder[i])/2*8, 0x8);
    }
    display_buffer();
}

// the coordinates of this function is relative position (/MOVE_W)
void draw_line(int sx, int sy, int ex, int ey) {
    double rate = (ey - sy)*1.0 / (ex - sx);
    int off = offset_screen(sx, sy);
    assert(off < SCR_SIZE);
    unsigned int i;
    int gapx = (sx > ex) ? -1 : 1;
    int gapy = rate * gapx;
    for (i = 0; ; ++i) {
        off = offset_screen(sx + i * gapx, sy + i * gapy);
        //printk("draw_line loop: %d\n", off);
        if (off == -1) {
            return;
        }
        draw_point(off, RED);
    }
}

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_timerMonsterAndYou() {

	prepare_buffer(); /* 准备缓冲区 */

    /*
      the coordinates of draw_string is absolute
    */
	draw_string(itoa(get_mfps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_mfps())) * 8, 14);
    // draw the counterdown timer
    draw_string(itoa(get_remaining()), 0, SCR_WIDTH/2, 0x8);
    draw_picture(head_bmp, HEAD_W, HEAD_H, off_to_screen());
    draw_line(getx(), gety(), AIM_X, AIM_Y);

	display_buffer(); /* 绘制缓冲区 */
}


