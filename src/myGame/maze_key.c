#include "common.h"
#include "string.h"

/*
  当按下一个键的时候, 键盘控制器将会发送该键的通码(make code); 当释放一个键的时候, 键盘控制器将会发送该键的断码(break code), 其中断码的值为通码的值+0x80.
 */
#define SIZE ((sizeof arrow_code)/(sizeof arrow_code[0]))

#define ENTER_CODE 28
#define ESC_CODE 1

static const int arrow_code[] = {
    72, 80, 75, 77//up, down, left, right
};
/* 对应键按下的标志位 */
static bool arrow_pressed[SIZE];

static bool enterPressed = FALSE;
static bool escPressed = FALSE;

void key_reinit() {
    unsigned int i;
    for (i = 0; i < SIZE; ++i) {
        arrow_pressed[i] = FALSE;
    }
    enterPressed = FALSE;
    escPressed = FALSE;
}

unsigned int arrow_size() {
    return SIZE;
}

void
press_dir(int scan_code) {
	int i;
	for (i = 0; i < SIZE; i ++) {
		if (arrow_code[i] == scan_code) {
			arrow_pressed[i] = TRUE;
		}
	}
    if (scan_code == ENTER_CODE) {
        enterPressed = TRUE;
    } else if (scan_code == ESC_CODE) {
        escPressed = TRUE;
    }

}

void
release_dir(int index) {
    //printk("size %d\n", SIZE);
	assert(0 <= index && index < SIZE);
	arrow_pressed[index] = FALSE;
}

bool
query_dir(int index) {
	assert(0 <= index && index < SIZE);
	return arrow_pressed[index];
}

/* key_code保存了上一次键盘事件中的扫描码 */
static volatile int key_code = 0;

int last_dir_key(void) {
	return key_code;
}

void
maze_key_event(int code) {
	key_code = code;
	press_dir(code);
}


bool againOr() {
    while (1) {
        // TODO can't understand why need a printk
        printk("");
        if (enterPressed) {
            return TRUE;
        } else if (escPressed) {
            return FALSE;
        }
    }
}

void release_enter() {
    enterPressed = TRUE;
}
void release_esc() {
    escPressed = FALSE;
}

#undef SIZE
