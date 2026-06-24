# Toy Projector Firmware

A modular **Embedded C firmware simulation** that demonstrates a packet-based image receiver pipeline for a toy projector. The project implements packet parsing, validation, image rendering, and unit testing using a layered firmware architecture.

---

## Features

* Modular firmware architecture
* Packet parsing and validation
* Image payload rendering
* Defensive error handling
* Unit testing without external frameworks
* Cross-platform build using Makefile (GCC/MinGW)

---

## Project Structure

```
Image_Projector_Firmware/
├── include/
│   ├── image.h
│   ├── packet.h
│   └── receiver.h
│
├── src/
│   ├── image.c
│   ├── main.c
│   ├── packet.c
│   └── receiver.c
│
├── tests/
│   └── test_packet.c
│
├── build/
├── Makefile
├── .gitignore
└── README.md
```

---

## Firmware Architecture

```
                 Incoming Packet
                        │
                        ▼
          receiver_handle_packet()
                        │
                        ▼
               packet_parse()
                        │
        ┌───────────────┴───────────────┐
        │                               │
   Validate Packet                 Report Error
        │
        ▼
  image_save_chunk()
        │
        ▼
 Display Image Payload
```

---

## Packet Format

| Offset | Field     | Size    | Description           |
| ------ | --------- | ------- | --------------------- |
| 0      | SOF       | 1 Byte  | Start of Frame (0x7D) |
| 1      | LEN       | 1 Byte  | Payload Length        |
| 2-3    | SEQ       | 2 Bytes | Sequence Number       |
| 4-5    | CH1 / CH2 | 2 Bytes | Control Bytes         |
| 6-N    | PAYLOAD   | N Bytes | Image Data            |
| Last   | EOF       | 1 Byte  | End of Frame (0xD7)   |

---

## Build Instructions

### Build Firmware

```bash
make
```

### Run Firmware

```bash
make run
```

### Run Unit Tests

```bash
make test
```

### Clean Build Files

```bash
make clean
```

---

## Project Highlights

* Designed a layered firmware architecture by separating packet processing, receiver logic, and image rendering into independent modules.
* Implemented packet validation using Start-of-Frame (SOF), End-of-Frame (EOF), payload length, and sequence checking.
* Developed reusable APIs using `const`-correct function interfaces.
* Added defensive programming techniques including NULL pointer validation and error handling.
* Built a lightweight unit test framework using custom assertion macros without external libraries.
* Organized the project using industry-standard directory structure (`src/`, `include/`, `tests/`, `build/`).

---

## Technologies Used

* Embedded C (C11)
* GCC / MinGW
* Makefile
* Git & GitHub
* Unit Testing
* Modular Firmware Design

---

## Future Improvements

* CRC-16 packet verification
* Packet retransmission support
* DMA-based packet reception
* UART driver integration
* Frame buffer implementation
* RTOS task-based packet processing

---

## Author

**Katuri Harsha Vardhan**

Firmware Engineer | Embedded Systems | Embedded C | Microcontrollers | Communication Protocols
