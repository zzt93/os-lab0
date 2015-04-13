#ifndef __MAZE_CONST_H__
#define __MAZE_CONST_H__

#include "device/video.h"

#define MOVE_WIDTH 10
// your coordinates relative to maze
#define INI_X 49
#define INI_Y 1
// screen index relative to maze
#define SCR_X 49
#define SCR_Y 16
// your size of move
#define GRIDS_X (MAZE_H/MOVE_WIDTH)
#define GRIDS_Y (MAZE_W/MOVE_WIDTH)
/* screen indices
#define SCR_INDEX_X (((MAZE_H * 2) / SCR_HEIGHT))
#define SCR_INDEX_Y (((MAZE_W * 2) / SCR_WIDTH))
*/

#define AIM_X 39
#define AIM_Y 100
#endif /* __MAZE_CONST_H__ */