CC = gcc
CFLAGS = -c -std=gnu99 -g -O3 -Werror -Wall -Wextra
SRCS = main.c grid.c file.c word.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main
PARAMS = ../example1.txt ../example1.trad

.PHONY : all run db clean

all: run clean

$(EXE) : $(OBJS)

run: $(EXE)
	./$(EXE) $(PARAMS)

db: $(EXE)
	gdb $(EXE)

clean:
	rm -f $(EXE) $(OBJS) out.txt
