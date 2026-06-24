#include "image.h"
#include <stdio.h>
#include <stdlib.h>

void image_erase(void)
{
    /*
     * On real hardware this would reset the framebuffer / display controller.
     * In the host simulation we clear the terminal.
     */
    system("clear");
}

void image_save_chunk(const uint8_t *chunk, uint16_t length)
{
    /*
     * On real hardware this DMA-transfers bytes to the projector's
     * image buffer.  In the host simulation we print raw ASCII art.
     *
     * NOTE: format specifier uses '%c' (lowercase) — '%C' (wide-char)
     * was a bug in the original code on standard C99/C11 compilers.
     */
    for (uint16_t i = 0; i < length; i++) {
        putchar((int)chunk[i]);
    }
}
