
all: 2.1 2.2

2.1: build/2.1
2.2: build/2.2

build/2.1: build 2.1/main.c Makefile
	gcc 2.1/main.c -pthread -lrt -lm -std=gnu17 -o $@

build/2.2: build 2.1/main.c Makefile
	gcc 2.1/main.c -lm -o $@ $$(/usr/xenomai/bin/xeno-config --skin=posix --cflags --ldflags)


build:
	mkdir $@