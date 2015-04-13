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
    bool again = TRUE;
    while (again) {
        maze_loop();
        again = againOr();
    }
	assert(0);
}
