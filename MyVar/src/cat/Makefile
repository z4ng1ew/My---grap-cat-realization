CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=201701L

SRCS=cat.c
OBJS=$(SRCS:.c=.o)
TARGET=s21_cat

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./$(TARGET) tests/test_file.txt
	./$(TARGET) tests/empty_file.txt
	./$(TARGET) tests/nonexistent_file.txt
	./$(TARGET) tests/special_characters.txt
	./$(TARGET) -n tests/numbered_lines.txt
	./$(TARGET) -s tests/empty_lines.txt
	./$(TARGET) -t tests/tabs.txt