#include "myGame/maze_key.h"
#include "myGame/scr.h"
#include "x86/x86.h"

static int all = 90;//90 second

void update_timer() {
    // counterdown timer
    all--;
}

int get_remaining() {
    return all;
}

void
update_monster(void) {
    // if time < some limit, initialize it
    // follow the trace to chase after you
}

bool
update_you() {

	disable_interrupt();
    unsigned int i;
    for (i = 0; i < arrow_size(); ++i) {
        if (query_dir(i)) {
            if (can_move(i)) {
                release_dir(i);
                return TRUE;
            } else {
                release_dir(i);
            }
        }
    }
	enable_interrupt();
	return FALSE;
}

