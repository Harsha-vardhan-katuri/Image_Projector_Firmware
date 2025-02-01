# Toy Projector Firmware

This project is a firmware for a toy projector that receives image data in chunks. It processes and displays the received image data. The firmware checks the validity of the received packet, extracts the image data, and displays it.

## Features

- **Packet Validation:** Checks the packet header for validity.
- **Image Data Handling:** Receives and displays image data in chunks.
- **System Clear:** Clears the screen before displaying new image data.
- **Image Data Output:** Outputs received image data to the console.

## Requirements

- A C compiler like `gcc` or an Integrated Development Environment (IDE) like Code::Blocks or Visual Studio Code.
- Basic knowledge of embedded systems and C programming.

## Functions

### 1. `eraseImageData()`
Clears the console screen to prepare for new data.

### 2. `saveImageData(uint8_t *imageDataChunk, uint16_t imageDataChunkLength)`
Saves a chunk of image data and outputs it to the console.

### 3. `imageReceiver(uint8_t *receivedBytes)`
Receives a packet of data and validates its header. If valid, it extracts the image data and calls `saveImageData` to handle it.

## Running the Project

### Step 1: Clone or Download the Project

You can clone the repository using Git or download the project files directly to your machine.

To clone the repository:

```bash
git clone https://your-repository-url.git
