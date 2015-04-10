#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "wall.h"


Dir* surrond();
void update(Dir, int*, int*);
int getx();
int gety();

void assume_move(Dir, int*, int*);
int off_to_screen();

#endif /* __CHARACTER_H__ */