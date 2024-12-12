CC = gcc
CFLAGS = -g -Wall -std=gnu99
CLEANUP = main

.SILENT:

all: main

main: main.c
	echo "  Creating main exec"
	${CC} ${CFLAGS} -o main main.c heap.c

.PHONY: clean
clean:
	for file in ${CLEANUP}; do \
		echo "  Cleaning $$file"; \
		rm -f $$file; \
	done


