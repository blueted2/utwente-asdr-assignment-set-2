
all: 2.1

2.1: build/2.1

build/2.1: build 2.1/main.c Makefile
	gcc 2.1/main.c -pthread -lrt -lm -std=gnu17 -o $@

build:
	mkdir $@