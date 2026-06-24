#include "receiver.h"
#include "packet.h"
#include "image.h"
#include <stdio.h>

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
