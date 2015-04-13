#include "game.h"
#include "irq.h"
#include "x86/x86.h"
#include "device/timer.h"
#include "test/test.h"
#include "device/palette.h"
#include "myGame/myGame.h"

void
game_init(void) {
	init_serial();
	init_timer();
	init_idt();
	init_intr();
	set_timer_intr_handler(maze_timer_event);
	set_keyboard_intr_handler(maze_key_event);

    write_palette();
	printk("game start!\n");
    //test_printk2();
	enable_interrupt();
	maze_loop();// game.c
	assert(0); /* main_loop是死循环，永远无法返回这里 */
}
