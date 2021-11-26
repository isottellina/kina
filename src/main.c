int kmain() {
    volatile char* vga_buffer = (char *)0xb8000;

    *vga_buffer = 'a';

    return 0;
}
