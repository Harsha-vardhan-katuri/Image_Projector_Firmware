# Toy Projector Firmware

A minimal embedded-C firmware simulation demonstrating a **packet-based image receiver pipeline** for a toy projector device.

```
                ┌──────────────────────────────────────────────────────┐
  Raw bytes ──► │  receiver_handle_packet()                            │
                │    └─► packet_parse()   ← validates SOF / LEN       │
                │          └─► image_save_chunk()  ← renders payload  │
                └──────────────────────────────────────────────────────┘
```

---

## Project Structure

```
toy_projector_fw/
├── include/
│   ├── packet.h        # Packet protocol constants & parse API
│   ├── image.h         # Image buffer / display API
│   └── receiver.h      # Top-level packet entry point
├── src/
│   ├── packet.c        # SOF / length validation
│   ├── image.c         # Payload rendering (terminal / framebuffer)
│   ├── receiver.c      # Glue: parse → render
│   └── main.c          # Host simulation with pre-recorded frames
├── tests/
│   └── test_packet.c   # Unit tests (no external framework required)
├── Makefile
└── README.md
```

---

## Packet Format

| Offset | Field      | Size | Description                     |
|--------|------------|------|---------------------------------|
| 0      | SOF        | 1 B  | Start-of-frame marker `0x7D`    |
| 1      | LEN        | 1 B  | Payload byte count              |
| 2–3    | SEQ        | 2 B  | Sequence number (hi, lo)        |
| 4–5    | CH1 / CH2  | 2 B  | Channel / control bytes         |
| 6…N    | PAYLOAD    | N B  | Image data                      |
| last   | EOF        | 1 B  | End-of-frame marker `0xD7`      |

---

## Build & Run

**Prerequisites:** `gcc`, `make` (any standard Linux / macOS / WSL environment)

```bash
# Build firmware simulator
make

# Run it (renders ASCII art to terminal)
make run

# Build & run unit tests
make test

# Clean build artefacts
make clean
```

---

## Bug Fixed vs Original

| # | Location          | Original              | Fixed                        |
|---|-------------------|-----------------------|------------------------------|
| 1 | `image.c`         | `printf("%C", …)`     | `putchar((int)chunk[i])`     |
| 2 | `receiver.c`      | `length > 0xFF` (always false on `uint8_t`) | Zero-length guard in `packet_parse()` |
| 3 | Architecture      | All logic in one file | Split across `packet / image / receiver` modules |

---

## Key Concepts Demonstrated

- **Layered firmware architecture** — protocol parsing decoupled from display logic
- **Defensive input validation** — NULL pointer and field range checks
- **Enum-based error propagation** — `PacketStatus` with string mapping
- **Zero-dependency unit testing** — custom `EXPECT_EQ` macro harness
- **`const`-correct API** — all input buffers marked `const uint8_t *`
