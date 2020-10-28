CC=gcc
CCFLAGS=-c -Wall -Wextra -Isrc

LD=gcc
LDFLAGS=

DEL=@rm
DELFLAGS=-frdv

MKDIR=mkdir
MKDIRFLAGS=-p

DBG=gdb
DBGFLAGS=--args

OBJ=main.o md5.o

DEBUGOBJ=$(patsubst %.o,bin/debug/%.o,$(OBJ))
RELEASEOBJ=$(patsubst %.o,bin/release/%.o,$(OBJ))

.PHONY: all clear debug release run

all:
	@echo "You need to add one of the following target :) : debug / release / clean / debug-run / release-run"


debug-run: debug
	$(DBG) $(DBGFLAGS) ./$< md5 test.txt

release-run: release
	./$<

clean:
	$(DEL) $(DELFLAGS) bin
	$(DEL) $(DELFLAGS) release
	$(DEL) $(DELFLAGS) debug

release: bin $(RELEASEOBJ)
	$(LD) $(LDFLAGS) -O2 -o $@ $(RELEASEOBJ)

debug: bin $(DEBUGOBJ)
	$(LD) $(LDFLAGS) -g -o $@ $(DEBUGOBJ)


bin:
	$(MKDIR) $(MKDIRFLAGS) bin/
	$(MKDIR) $(MKDIRFLAGS) bin/debug
	$(MKDIR) $(MKDIRFLAGS) bin/release

bin/debug/%.o: src/%.c src/*.h
	$(CC) $(CCFLAGS) -g -o $@ $<

bin/release/%.o: src/%.c src/*.h
	$(CC) $(CCFLAGS) -O2 -o $@ $<
