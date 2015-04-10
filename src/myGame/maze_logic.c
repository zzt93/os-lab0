#include "myGame/maze_key.h"
#include "myGame/wall.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"

static int all = 60;//60 second

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
        if (query_key2(i) && can_move(i)) {
            return TRUE;
        }
    }
	enable_interrupt();
	return FALSE;
}

