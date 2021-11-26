#include"tty.h"

int kmain(void *header) {
    tty_clear_screen();
    tty_printf("Hello world! %p\n", header);

    return 0;
}
