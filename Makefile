CC = gcc
CFLAGS = -c -std=gnu99 -O3 -Werror -Wall -Wextra
SRCS = main.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main

.PHONY : all run clean

all: run

$(EXE) : $(OBJS)

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)
