CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=201701L

SRCS=cat.c
OBJS=$(SRCS:.c=.o)
TARGET=s21_cat

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)