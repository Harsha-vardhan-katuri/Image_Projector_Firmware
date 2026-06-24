#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

/* ─── API ────────────────────────────────────────────────────── */
/**
 * @brief  Clear / reset the image buffer (e.g. clear terminal display).
 */
void image_erase(void);

/**
 * @brief  Append a chunk of raw image data to the display output.
 *
 * @param  chunk   Pointer to payload bytes.
 * @param  length  Number of bytes to consume.
 */
void image_save_chunk(const uint8_t *chunk, uint16_t length);

#endif /* IMAGE_H */
