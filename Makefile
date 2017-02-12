CC = gcc
CFLAGS = -c -std=gnu99 -g -O3 -Werror -Wall -Wextra
SRCS = main.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main
PARAMS = in.txt 20

.PHONY : all run db clean

all: run

$(EXE) : $(OBJS)

run: $(EXE)
	./$(EXE) $(PARAMS)

db: $(EXE)
	gdb $(EXE)

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)
