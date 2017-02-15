CC = gcc
CFLAGS = -c -std=gnu99 -g -O3 -Werror -Wall -Wextra
SRCS = main.c
OBJS = $(subst .c,.o,$(SRCS))
EXE = main

.PHONY : run clean

run: $(EXE)
	./$(EXE) $(PARAMS)

$(EXE) : $(OBJS)

clean:
	rm -f $(EXE) $(OBJS) out.txt
