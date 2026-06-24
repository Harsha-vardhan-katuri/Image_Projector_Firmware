# ─── Toy Projector Firmware — Makefile ───────────────────────────────────────

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -I include

SRC_DIR  := src
TEST_DIR := tests
BUILD    := build

FW_SRCS  := $(SRC_DIR)/packet.c $(SRC_DIR)/image.c $(SRC_DIR)/receiver.c $(SRC_DIR)/main.c
FW_BIN   := $(BUILD)/toy_projector

TEST_SRCS := $(SRC_DIR)/packet.c $(TEST_DIR)/test_packet.c
TEST_BIN  := $(BUILD)/test_packet

# Platform-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BUILD) mkdir $(BUILD)
    RM    = if exist $(BUILD) rmdir /s /q $(BUILD)
    RUN   =
    EXE   = .exe
else
    MKDIR = mkdir -p $(BUILD)
    RM    = rm -rf $(BUILD)
    RUN   = ./
    EXE   =
endif

FW_BIN   := $(FW_BIN)$(EXE)
TEST_BIN := $(TEST_BIN)$(EXE)

.PHONY: all
all: $(FW_BIN) test

$(FW_BIN): $(FW_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test
test: $(TEST_BIN)
	@echo ""
	@echo Running unit tests...
	$(RUN)$(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD):
	$(MKDIR)

.PHONY: clean
clean:
	$(RM)

.PHONY: run
run: $(FW_BIN)
	$(RUN)$(FW_BIN)