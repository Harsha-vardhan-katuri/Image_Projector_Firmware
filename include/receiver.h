/**
 * @file receiver.h
 * @brief Packet receiver interface.
 *
 * Receives raw packets, validates them using the packet parser,
 * and forwards the image payload to the rendering module.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>

/**
 * @brief Process a received packet.
 *
 * Validates the packet and forwards the payload to the image
 * rendering module.
 *
 * @param buf Pointer to the received packet buffer.
 */
void receiver_handle_packet(const uint8_t *buf);

#endif /* RECEIVER_H */