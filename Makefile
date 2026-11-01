CC = gcc
CPPFLAGS += -Iinclude
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic

OUTPUT_DIR := output
TARGET := $(OUTPUT_DIR)/bpfdoor
SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c,$(OUTPUT_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(OUTPUT_DIR)/%.o: src/%.c | $(OUTPUT_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OUTPUT_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJECTS) $(DEPS) $(TARGET)

-include $(DEPS)
