CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lm

.PHONY: all clean
all: main.cpp
	$(CC) $(CFLAGS) -o calculator main.cpp calc.cpp $(LDLIBS)

clean:
	if [ -f calculator ]; then rm calculator; fi
