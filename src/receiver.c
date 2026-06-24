/**
 * @file receiver.c
 * @brief Packet receiver implementation.
 *
 * Receives raw packets, validates them using the packet parser,
 * and forwards valid image payloads to the image rendering module.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */
#include "receiver.h"
#include "packet.h"
#include "image.h"
#include <stdio.h>

/**
 * @brief Process a received packet.
 *
 * Validates the packet and forwards the payload to the
 * image rendering module.
 *
 * @param buf Pointer to the received packet buffer.
 */
void receiver_handle_packet(const uint8_t *buf)
{
    uint8_t payload_len = 0;

    PacketStatus status = packet_parse(buf, &payload_len);
    if (status != PKT_OK) {
        fprintf(stderr, "[receiver] Packet dropped — %s\n",
                packet_status_str(status));
        return;
    }

    image_save_chunk(&buf[OFFSET_PAYLOAD], payload_len);
}
