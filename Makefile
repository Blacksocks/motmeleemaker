CC = gcc
CFLAGS = -c -std=gnu99 -g -O3 -Werror -Wall -Wextra
SRCS = main.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main

.PHONY : all run db clean

all: run

$(EXE) : $(OBJS)

run: $(EXE)
	./$(EXE)

db: $(EXE)
	gdb $(EXE)

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)
