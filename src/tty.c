#include "tty.h"

#define POSITION(x, y) ((y * 80 + x) << 1)

volatile char *vga_buffer = (char *)0xb8000;
int cursor_x = 0, cursor_y = 0;

void tty_clear_screen(void) {
    for (int i = 0; i < (80 * 25); i++)
        vga_buffer[i << 1] = ' ';
}

int tty_printc(char c) {
    switch (c) {
        case '\n':
            cursor_x = 0;
            cursor_y++;
            break;
        default:
            vga_buffer[POSITION(cursor_x, cursor_y)] = c;

            cursor_x++;
            if (cursor_x == 80) {
                cursor_x = 0;
                cursor_y++;
            }
            break;
    }
    return 0;
}

int tty_prints(char *s) {
    for (int i = 0; s[i]; i++)
        tty_printc(s[i]);

    return 0;
}
