# Image Projector Firmware - README

## Overview
This project involves receiving image data packets transmitted over a USB connection to a toy projector with limited memory. The image is transmitted in multiple packets, and the receiver must validate each packet, reconstruct the image, and store it in memory. If any packet is lost or corrupted, the entire image transmission is discarded.

## Packet Structure
Each packet follows the defined structure:

| Field | Size | Description |
|--------|------|-------------|
| Header | 1 byte | Fixed value `0x7D`, marks the beginning of the packet. |
| Packet Length | 1 byte | Total packet size in bytes. |
| Packet Number | 2 bytes | Order of the packet (MSB first). |
| Total Image Size | 2 bytes | Total size of the image (MSB first). |
| Payload | Payload size depends on packet length | Image data. |
| CRC-16/XMODEM | 2 bytes | Checksum computed over Packet Length, Packet Number, Total Image Size, and Payload (MSB first). |
| Footer | 1 byte | Fixed value `0xD7`, marks the end of the packet. |

## Error Handling
- If a packet is missing or contains an invalid CRC, the entire image transmission is aborted.
- The `eraseImageData()` function is called when receiving the first packet to clear memory.
- The `saveImageData()` function is used to store received valid packets.
- The function `imageReceiver()` is invoked for every received packet to process it.

## Code Implementation
The provided code follows these steps:
1. **Packet Validation:**
   - Check for valid `Header` (`0x7D`) and `Footer` (`0xD7`).
   - Validate `CRC-16/XMODEM` checksum.
2. **Handling First Packet:**
   - Erase memory (`eraseImageData()`) when the first packet (packet number `1`) is received.
3. **Image Assembly:**
   - Store valid packets in memory (`saveImageData()`).
4. **Error Handling:**
   - If an error occurs (corrupt packet, missing packet, invalid CRC), erase image memory and discard remaining packets.

### Function Breakdown
- `eraseImageData()`: Clears memory before receiving a new image.
- `saveImageData(payload)`: Saves the valid image data received.
- `imageReceiver(packet)`: Processes each received packet, validates it, extracts image data, and stores it if valid.

### Example Flow
1. The first packet arrives, triggering `eraseImageData()`.
2. Each subsequent packet is validated and stored using `saveImageData()`.
3. If a packet is corrupt or missing, `eraseImageData()` is called to discard the entire image.

## Dependencies
- CRC-16/XMODEM checksum calculation.
- USB data reception handling.


## How to Clone the Repository
To get a local copy of the project, use the following command:
```sh
git clone <repository_url>
```

## How to Compile
Ensure you have a C/C++ compiler installed (e.g., GCC). Navigate to the project directory and compile the code using:
```sh
gcc -o Image_projector_firmware Image_projector_firmware.c
```

## How to Run
Run the compiled executable:
```sh
./Image_projector_firmware
```

This will start listening for image packets and process them accordingly.

## License
This project is released under the MIT License.

## Contributors
- Katuri Harsha Vardhan
