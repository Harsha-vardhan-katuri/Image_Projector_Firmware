#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>

/**
 * @brief  Process one incoming packet buffer.
 *
 *  Validates the packet header/length, then forwards the payload
 *  to the image layer.  Call this once per received frame.
 *
 * @param  buf  Pointer to the raw byte buffer (minimum PACKET_HEADER_SIZE bytes).
 */
void receiver_handle_packet(const uint8_t *buf);

#endif /* RECEIVER_H */
