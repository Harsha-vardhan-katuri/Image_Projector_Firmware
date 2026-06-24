/**
 * @file image.h
 * @brief Image rendering interface for the Toy Projector Firmware.
 *
 * Provides APIs for clearing the image buffer and rendering
 * received image payload data.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

/**
 * @brief Clear or reset the image buffer.
 *
 * Clears the current display contents before rendering a new frame.
 */
void image_erase(void);

/**
 * @brief Render an image payload chunk.
 *
 * Appends the received image payload to the display output.
 *
 * @param chunk Pointer to the image payload.
 * @param length Number of payload bytes.
 */
void image_save_chunk(const uint8_t *chunk, uint16_t length);

#endif /* IMAGE_H */