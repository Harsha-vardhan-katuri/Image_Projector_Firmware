# ─── Toy Projector Firmware — Makefile ───────────────────────────────────────
#
# Targets:
#   make            Build the firmware simulator binary
#   make test       Build & run unit tests
#   make clean      Remove all build artefacts
#   make all        Build simulator + run tests

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -I include

SRC_DIR  := src
TEST_DIR := tests
BUILD    := build

FW_SRCS  := $(SRC_DIR)/packet.c $(SRC_DIR)/image.c $(SRC_DIR)/receiver.c $(SRC_DIR)/main.c
FW_BIN   := $(BUILD)/toy_projector

TEST_SRCS := $(SRC_DIR)/packet.c $(TEST_DIR)/test_packet.c
TEST_BIN  := $(BUILD)/test_packet

# ─── Default target ───────────────────────────────────────────
.PHONY: all
all: $(FW_BIN) test

# ─── Firmware simulator ───────────────────────────────────────
$(FW_BIN): $(FW_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

# ─── Unit tests ───────────────────────────────────────────────
.PHONY: test
test: $(TEST_BIN)
	@echo ""
	@echo "Running unit tests..."
	@./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

# ─── Helpers ──────────────────────────────────────────────────
$(BUILD):
	mkdir -p $(BUILD)

.PHONY: clean
clean:
	rm -rf $(BUILD)

.PHONY: run
run: $(FW_BIN)
	@./$(FW_BIN)
