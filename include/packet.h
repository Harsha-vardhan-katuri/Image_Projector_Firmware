#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <stdbool.h>

/* ─── Protocol Constants ─────────────────────────────────────── */
#define PACKET_HEADER_BYTE      0x7D
#define PACKET_TERMINATOR_BYTE  0xD7
#define PACKET_HEADER_SIZE      6u   /* [SOF][LEN][SEQ_HI][SEQ_LO][CH1][CH2] */

/* ─── Packet Field Offsets ───────────────────────────────────── */
#define OFFSET_SOF      0
#define OFFSET_LEN      1
#define OFFSET_SEQ_HI   2
#define OFFSET_SEQ_LO   3
#define OFFSET_CH1      4
#define OFFSET_CH2      5
#define OFFSET_PAYLOAD  6

/* ─── Packet Validation Result ───────────────────────────────── */
typedef enum {
    PKT_OK              = 0,
    PKT_ERR_NULL_PTR    = -1,
    PKT_ERR_BAD_HEADER  = -2,
    PKT_ERR_BAD_LENGTH  = -3,
} PacketStatus;

/* ─── API ────────────────────────────────────────────────────── */
/**
 * @brief  Validate and extract fields from a raw received byte buffer.
 *
 * @param  buf        Pointer to raw packet bytes (caller-owned).
 * @param  out_len    Populated with the payload byte count on success.
 * @return PacketStatus
 */
PacketStatus packet_parse(const uint8_t *buf, uint8_t *out_len);

/**
 * @brief  Return a human-readable string for a PacketStatus code.
 */
const char *packet_status_str(PacketStatus s);

#endif /* PACKET_H */
