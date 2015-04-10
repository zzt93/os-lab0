#include "myGame/myGame.h"
#include "string.h"
#include "device/video.h"
#include "myGame/character.h"

#include "myGame/head_bmp"
/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_timerMonsterAndYou() {

	prepare_buffer(); /* 准备缓冲区 */

	/* 绘制每个字符 */
	/* 绘制命中数、miss数、最后一次按键扫描码和fps */
    /*
	draw_string(itoa(-1), SCR_HEIGHT - 8, 0, 48);
	hit = itoa(-1);
	draw_string(hit, 0, SCR_WIDTH - strlen(hit) * 8, 10);
	miss = itoa(-1);
	draw_string(miss, SCR_HEIGHT - 8, SCR_WIDTH - strlen(miss) * 8, 12);
	draw_string(itoa(get_fps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);
    */
    // draw the counterdown timer
    draw_string(itoa(get_remaining()), 0, SCR_WIDTH/2, 0x8);
    draw_picture(head_bmp, HEAD_W, HEAD_H, off_to_screen());

	display_buffer(); /* 绘制缓冲区 */
}

