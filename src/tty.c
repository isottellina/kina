#include<stdarg.h>
#include "tty.h"

#define POSITION(x, y) ((y * 80 + x) << 1)
#define CLEAN_BUFFER() for (int i = 0; i < 100; i++) { buffer[i] = 0; }

volatile char *vga_buffer = (char *)0xb8000;
int cursor_x = 0, cursor_y = 0;

void tty_clear_screen(void) {
    for (int i = 0; i < (80 * 25); i++)
        vga_buffer[i << 1] = ' ';
}

void _increase_line() {
    cursor_x = 0;
    cursor_y++;

    if (cursor_y == 25) {
        cursor_y = 24;

        // Scroll everything one line
        for (int i = 0; i < (80 * 24); i++) {
            vga_buffer[i << 1] = vga_buffer[(i + 80) << 1];
        }

        // Empty out other line
        for (int i = 0; i < 80; i++) {
            vga_buffer[POSITION(i, 24)] = ' ';
        }
    }
}

int tty_printc(char c) {
    switch (c) {
        case '\n':
            _increase_line();
            break;
        default:
            vga_buffer[POSITION(cursor_x, cursor_y)] = c;

            cursor_x++;
            if (cursor_x == 80) {
                _increase_line();
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

void itoa(char *buffer, int n, int base) {
    int i = 0;

    do {
        int a = n % base;
        buffer[i++] = (a < 0xa) ? ('0' + a) : ('a' + a - 10);

        n /= base;
    } while(n);

    i--;
    for (int j = 0; j < i; j++, i--) {
        char c = buffer[j];
        buffer[j] = buffer[i];
        buffer[i] = c;
    }
}

int tty_printf(char *s, ...) {
    char buffer[100];
    va_list ap;
    va_start(ap, s);

    for (int i = 0; s[i]; i++) {
        if ((s[i] == '%') && s[i + 1]) {
            i++;

            switch (s[i]) {
                case 'd':
                    CLEAN_BUFFER();
                    itoa(buffer, va_arg(ap, int), 10);
                    tty_prints(buffer);
                    break;
                case 'p':
                    CLEAN_BUFFER();
                    itoa(buffer, va_arg(ap, int), 16);
                    tty_prints("0x");
                    tty_prints(buffer);
                    break;
                case 's':
                    tty_prints(va_arg(ap, char *));
                    break;
                case '%':
                    tty_printc('%');
                    break;
            }
        } else {
            tty_printc(s[i]);
        }
    }

    va_end(ap);
    return 0;
}
