# Makefile for C and GTK4 Examples

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
GTK_LIBS = $(shell pkg-config --libs gtk4)

# Find all .c files in examples subdirectories
C_SRCS = $(shell find . -name "*.c" -not -path "*/.*")
# Generate executable names by removing .c extension
BINS = $(C_SRCS:.c=)

.PHONY: all clean help

all: $(BINS)

# Rule for standard C examples (Phase 1: Chapters 01-10)
# We use a pattern match that covers any subdirectory starting with chapter_0 or chapter_10
chapter_0%/examples/%: chapter_0%/examples/%.c
	@echo "Building C example: $<"
	$(CC) $(CFLAGS) $< -o $@

chapter_10/examples/%: chapter_10/examples/%.c
	@echo "Building C example: $<"
	$(CC) $(CFLAGS) $< -o $@

# Rule for GTK4 examples (Phase 2: Chapters 11-19)
chapter_11/examples/%: chapter_11/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_12/examples/%: chapter_12/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_13/examples/%: chapter_13/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_14/examples/%: chapter_14/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_15/examples/%: chapter_15/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_16/examples/%: chapter_16/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_17/examples/%: chapter_17/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_18/examples/%: chapter_18/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

chapter_19/examples/%: chapter_19/examples/%.c
	@echo "Building GTK4 example: $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< $(GTK_LIBS) -o $@

clean:
	@echo "Cleaning up executables..."
	rm -f $(BINS)

help:
	@echo "Available commands:"
	@echo "  make         - Build all C and GTK4 examples"
	@echo "  make clean   - Remove all compiled executables"
	@echo "  make help    - Show this help message"
	@echo ""
	@echo "Detected examples:"
	@for bin in $(BINS); do echo "  $$bin"; done
