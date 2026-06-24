/**
 * @file image.c
 * @brief Image rendering implementation.
 *
 * Implements image rendering functions for the Toy Projector Firmware.
 * In the host simulation, image payloads are rendered as ASCII art
 * in the terminal.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */
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
/**
 * @brief Render an image payload.
 *
 * Prints the payload as ASCII art in the host simulation.
 *
 * @param chunk Pointer to the image payload.
 * @param length Payload size in bytes.
 */
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
