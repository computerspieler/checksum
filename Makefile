SRCS=$(wildcard src/*.c)
DEPS=$(patsubst src/%,bin/deps/%.d,$(SRCS))
OBJS=$(patsubst src/%,bin/objs/%.o,$(SRCS))

CC=gcc
LD=gcc
CCFLAGS=-Wall -Wextra -g -ggdb -Isrc -c
LDFLAGS=-g -ggdb

all: bin/debug

clean:
	rm -rf bin

-include $(DEPS)

bin/debug: $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

bin/objs/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

bin/deps/%.c.d: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst bin/deps/%,bin/objs/%,$@)

