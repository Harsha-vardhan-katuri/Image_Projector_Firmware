/**
 * @file packet.h
 * @brief Packet parser interface for the Toy Projector Firmware.
 *
 * Defines the packet format, protocol constants, status codes,
 * and parsing APIs used by the receiver module.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */

#ifndef PACKET_H
#define PACKET_H

#include <stdbool.h>
#include <stdint.h>

/* ─── Protocol Constants ─────────────────────────────────────── */

#define PACKET_HEADER_BYTE      0x7D
#define PACKET_TERMINATOR_BYTE  0xD7
#define PACKET_HEADER_SIZE      6u

/* ─── Packet Field Offsets ───────────────────────────────────── */

#define OFFSET_SOF      0
#define OFFSET_LEN      1
#define OFFSET_SEQ_HI   2
#define OFFSET_SEQ_LO   3
#define OFFSET_CH1      4
#define OFFSET_CH2      5
#define OFFSET_PAYLOAD  6

/**
 * @brief Packet parser status codes.
 */
typedef enum
{
    PKT_OK             = 0,
    PKT_ERR_NULL_PTR   = -1,
    PKT_ERR_BAD_HEADER = -2,
    PKT_ERR_BAD_LENGTH = -3
} PacketStatus;

/**
 * @brief Validate and parse a received packet.
 *
 * Validates the packet header and payload length before extracting
 * packet information.
 *
 * @param buf Pointer to the received packet buffer.
 * @param out_len Returns the payload length on success.
 *
 * @return PacketStatus indicating the parsing result.
 */
PacketStatus packet_parse(const uint8_t *buf, uint8_t *out_len);

/**
 * @brief Convert a packet status into a readable string.
 *
 * @param s Packet status code.
 *
 * @return Constant string describing the status.
 */
const char *packet_status_str(PacketStatus s);

#endif /* PACKET_H */