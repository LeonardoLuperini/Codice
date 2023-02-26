CC 		:= gcc
CFLAGS 	:= -Wall -pedantic
EXE 	:= main.out
SRCDIR	:= ./src
SRCS	:= $(wildcard $(SRCDIR)/*.c)
OBJDIR	:= ./obj
OBJS	:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
SCRIPT 	:= script.sh
TESTDIR := testdir

.PHONY: all clean test1 test2

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $?

clean:
	rm -f $(EXE) $(wildcard $(OBJDIR)/*.o)

test1: $(SCRIPT)
	chmod +x $(SCRIPT)
	./$(SCRIPT) ./$(TESTDIR)

test2: $(EXE)
	./$(EXE) ./$(TESTDIR)
