# -- Directories --
# Root directory
ROOT ?= .

# Input directories
INCLUDE ?= $(ROOT)/include
SRC ?= $(ROOT)/src

# Build directories
BUILD ?= $(ROOT)/build
OBJ ?= $(BUILD)/obj


# -- Files --
# Prerequisites
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
INCLUDES := $(addprefix -I,$(INCLUDE))

# Targets
TARGET ?= $(BUILD)/$(shell basename "$(CURDIR)")


# -- Commands --
# Shell
MKDIR = mkdir -p
RM = rm -rfv

# Compiler
CC = cc
CFLAGS = -Wall -g -std=c17 $(INCLUDES)


# -- Recipies --
.PHONY: all
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	@$(MKDIR) $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


# Run target executable
.PHONY: run
run: $(TARGET)
	@$(TARGET)


# Clean project directory
.PHONY: clean
clean:
	@$(RM) $(BUILD)
