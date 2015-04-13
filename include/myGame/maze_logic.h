#ifndef __MAZE_LOGIC_H__
#define __MAZE_LOGIC_H__

void update_timer();
void update_monster();
bool update_you();

int get_remaining();

typedef enum {
    WIN, LOSE, LET,
} Result;

Result winOrLose();
#endif /* __MAZE_LOGIC_H__ */