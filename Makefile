CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lm

.PHONY: all clean
all: main.c calc.c
	$(CC) $(CFLAGS) -o calculator main.c calc.c $(LDLIBS)

clean:
	if [ -f calculator ]; then rm calculator; fi
