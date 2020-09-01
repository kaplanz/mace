# Root directory
ROOT ?= .
# Input directories
INCLUDE ?= $(ROOT)/include
SRC ?= $(ROOT)/src
# Build directories
BUILD ?= $(ROOT)/build
OBJ ?= $(BUILD)/obj

# Prerequisites
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
INCLUDES := $(addprefix -I,$(INCLUDE))
# Targets
TARGET ?= $(BUILD)/$(shell basename "$(CURDIR)")

# Commands
MKDIR = mkdir -p
RM = rm -rfv
# Compiler
CC = cc
CFLAGS = -Wall -g -std=c17 $(INCLUDES)

# Build target executable
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	@$(MKDIR) $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# Run target executable
.PHONY: run
run: $(TARGET)
	@$(TARGET)

# Clean build directory
.PHONY: clean
clean:
	@$(RM) $(BUILD)
