#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "wall.h"


Dir* surrond();
void update(Dir);
int getx();
int gety();

void assume_move(Dir, int*, int*);
int off_to_screen();
int offset_screen(int x, int y);

#endif /* __CHARACTER_H__ */