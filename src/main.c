#include"tty.h"
#include"multiboot.h"

int kmain(multiboot_header_t *header) {
    tty_clear_screen();
    tty_printf("Reading multiboot information...\n");
    // Here we put the reading of multiboot informations when we need them

    return 0;
}
