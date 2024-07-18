CC=gcc
CFLAGS=-Wall -Wextra -g
DEPS=-lncurses -lm

SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c,obj/%.o,$(SRCS))
BIN=telescope.sh

all: $(BIN)

echo:
	echo $(SRCS)
	echo $(OBJS)

$(BIN): $(OBJS)
	echo Linking $(OBJS) into $(BIN)
	$(CC) -o $@ $^ $(DEPS)

obj/%.o:src/%.c
	echo Compiling $(SRCS) into $(OBJS)
	mkdir -p obj/
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(BIN) $(OBJS)

