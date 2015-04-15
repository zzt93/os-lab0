#ifndef __MAZE_CONST_H__
#define __MAZE_CONST_H__

#include "device/video.h"

#define MOVE_WIDTH 8
// your coordinates relative to maze
#define INI_X (490 / MOVE_WIDTH)
#define INI_Y (10 / MOVE_WIDTH)
// screen index relative to maze
#define SCR_X INI_X
#define SCR_Y (SCR_WIDTH / 2 / MOVE_WIDTH)
// your size of move
#define GRIDS_X (MAZE_H/MOVE_WIDTH)
#define GRIDS_Y (MAZE_W/MOVE_WIDTH)
/* screen indices
#define SCR_INDEX_X (((MAZE_H * 2) / SCR_HEIGHT))
#define SCR_INDEX_Y (((MAZE_W * 2) / SCR_WIDTH))
*/

#define AIM_X (379 / MOVE_WIDTH)
#define AIM_Y (1000 / MOVE_WIDTH)

#define TO_GRID_CEN MOVE_WIDTH/2

#endif /* __MAZE_CONST_H__ */