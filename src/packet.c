/**
 * @file packet.c
 * @brief Packet parser implementation.
 *
 * Implements packet validation, payload length extraction,
 * and packet status reporting for the Toy Projector Firmware.
 *
 * @author Katuri Harsha Vardhan
 * @date 2026
 */
#include "packet.h"
#include <stdio.h>

/**
 * @brief Validate a received packet.
 *
 * Checks the packet header and payload length before returning
 * the payload size.
 *
 * @param buf Pointer to the received packet.
 * @param out_len Returns the payload length.
 *
 * @return PacketStatus indicating the validation result.
 */
PacketStatus packet_parse(const uint8_t *buf, uint8_t *out_len)
{
    if (buf == NULL || out_len == NULL) {
        return PKT_ERR_NULL_PTR;
    }

    /* Validate Start-Of-Frame byte */
    if (buf[OFFSET_SOF] != PACKET_HEADER_BYTE) {
        fprintf(stderr, "[packet] Invalid header: expected 0x%02X, got 0x%02X\n",
                PACKET_HEADER_BYTE, buf[OFFSET_SOF]);
        return PKT_ERR_BAD_HEADER;
    }

    /* Length field is a single byte — always valid as uint8_t, but
       guard against a zero-length payload being silently accepted. */
    uint8_t length = buf[OFFSET_LEN];
    if (length == 0) {
        fprintf(stderr, "[packet] Zero-length payload\n");
        return PKT_ERR_BAD_LENGTH;
    }

    *out_len = length;
    return PKT_OK;
}

const char *packet_status_str(PacketStatus s)
{
    switch (s) {
        case PKT_OK:              return "OK";
        case PKT_ERR_NULL_PTR:    return "Null pointer";
        case PKT_ERR_BAD_HEADER:  return "Bad header byte";
        case PKT_ERR_BAD_LENGTH:  return "Invalid length";
        default:                  return "Unknown error";
    }
}
