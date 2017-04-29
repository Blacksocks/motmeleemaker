CC = gcc
CFLAGS = -c -std=gnu99 -g -O3 -Werror -Wall -Wextra
SRCS = word.c grid.c file.c main.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main
OUT = ../out.txt
PARAMS = ../in.txt $(OUT)

.PHONY : all run db clean

all: run clean

$(EXE) : $(OBJS)

run: $(EXE)
	./$(EXE) $(PARAMS)

db: $(EXE)
	gdb $(EXE)

clean:
	rm -f $(OBJS)

clean-all: clean
	rm -f $(EXE)
