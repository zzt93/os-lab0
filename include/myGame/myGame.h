#ifndef __MYGAME_H__
#define __MYGAME_H__


#include "common.h"
#include "adt/linklist.h"

/* 按键相关 */
#include "maze_key.h"
/* 游戏逻辑相关 */
#include "maze_logic.h"

#include "maze_draw.h"
/* 随机数 */
#include "lib/rand.h"

#include "wall.h"
/* 初始化串口 */
void init_serial();

/* 中断时调用的函数 */
void maze_timer_event(void);
void maze_key_event(int scan_code);

/* 主循环 */
void maze_loop(void);
int get_mfps();

#endif /* __MYGAME_H__ */
