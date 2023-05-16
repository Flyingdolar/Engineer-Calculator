CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lm

.PHONY: all debug clean
all: main.cpp
	$(CC) -std=c++17 -o calculator main.cpp calc.cpp parser.cpp $(LDLIBS)

debug: main.cpp
	$(CC) $(CFLAGS) -g -o calculator main.cpp calc.cpp parser.cpp $(LDLIBS)

clean:
	if [ -f calculator ]; then rm calculator; fi
