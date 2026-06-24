/**
 * @file  test_packet.c
 * @brief Minimal unit tests for packet_parse() — no external framework needed.
 *
 * Build & run:
 *   gcc -I../include ../src/packet.c test_packet.c -o test_packet && ./test_packet
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "packet.h"

/* ─── Tiny test harness ──────────────────────────────────────── */
static int g_pass = 0;
static int g_fail = 0;

#define EXPECT_EQ(actual, expected, desc)                                      \
    do {                                                                       \
        if ((actual) == (expected)) {                                          \
            printf("  [PASS] %s\n", desc);                                    \
            g_pass++;                                                          \
        } else {                                                               \
            printf("  [FAIL] %s  (got %d, expected %d)\n",                   \
                   desc, (int)(actual), (int)(expected));                      \
            g_fail++;                                                          \
        }                                                                      \
    } while (0)

/* ─── Test cases ─────────────────────────────────────────────── */

static void test_valid_packet(void)
{
    puts("test_valid_packet:");
    /* Minimal valid packet: SOF + LEN=1 + 4 header bytes */
    uint8_t buf[] = { 0x7D, 0x20, 0x00, 0x01, 0x03, 0xB3, 0xAA };
    uint8_t len   = 0;
    PacketStatus s = packet_parse(buf, &len);
    EXPECT_EQ(s,   PKT_OK, "status is PKT_OK");
    EXPECT_EQ(len, 0x20,   "length field extracted correctly");
}

static void test_bad_header(void)
{
    puts("test_bad_header:");
    uint8_t buf[] = { 0xAA, 0x20, 0x00, 0x01, 0x03, 0xB3, 0xFF };
    uint8_t len   = 0;
    PacketStatus s = packet_parse(buf, &len);
    EXPECT_EQ(s, PKT_ERR_BAD_HEADER, "wrong SOF byte → PKT_ERR_BAD_HEADER");
}

static void test_zero_length(void)
{
    puts("test_zero_length:");
    uint8_t buf[] = { 0x7D, 0x00, 0x00, 0x01, 0x03, 0xB3 };
    uint8_t len   = 0;
    PacketStatus s = packet_parse(buf, &len);
    EXPECT_EQ(s, PKT_ERR_BAD_LENGTH, "zero LEN byte → PKT_ERR_BAD_LENGTH");
}

static void test_null_buffer(void)
{
    puts("test_null_buffer:");
    uint8_t len = 0;
    PacketStatus s = packet_parse(NULL, &len);
    EXPECT_EQ(s, PKT_ERR_NULL_PTR, "NULL buf → PKT_ERR_NULL_PTR");
}

static void test_null_out_len(void)
{
    puts("test_null_out_len:");
    uint8_t buf[] = { 0x7D, 0x10, 0x00, 0x01, 0x03, 0xB3 };
    PacketStatus s = packet_parse(buf, NULL);
    EXPECT_EQ(s, PKT_ERR_NULL_PTR, "NULL out_len → PKT_ERR_NULL_PTR");
}

static void test_status_strings(void)
{
    puts("test_status_strings:");
    /* Just verify the function returns a non-NULL string for each code */
    const char *ok  = packet_status_str(PKT_OK);
    const char *nh  = packet_status_str(PKT_ERR_BAD_HEADER);
    const char *nl  = packet_status_str(PKT_ERR_BAD_LENGTH);
    const char *np  = packet_status_str(PKT_ERR_NULL_PTR);
    const char *unk = packet_status_str((PacketStatus)99);
    EXPECT_EQ(ok  != NULL, 1, "PKT_OK string non-NULL");
    EXPECT_EQ(nh  != NULL, 1, "PKT_ERR_BAD_HEADER string non-NULL");
    EXPECT_EQ(nl  != NULL, 1, "PKT_ERR_BAD_LENGTH string non-NULL");
    EXPECT_EQ(np  != NULL, 1, "PKT_ERR_NULL_PTR string non-NULL");
    EXPECT_EQ(unk != NULL, 1, "unknown code string non-NULL");
}

/* ─── Runner ─────────────────────────────────────────────────── */
int main(void)
{
    puts("=== Packet Parser Unit Tests ===\n");

    test_valid_packet();
    test_bad_header();
    test_zero_length();
    test_null_buffer();
    test_null_out_len();
    test_status_strings();

    printf("\n=== Results: %d passed, %d failed ===\n", g_pass, g_fail);
    return (g_fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
