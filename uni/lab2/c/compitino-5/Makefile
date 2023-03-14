CC 		:= gcc
CFLAGS 	:= -Wall -pedantic
CPPFLAGS:= -pthread
LDLIBS  := -lm -lrt
LDFLAGS := -pthread $(LDLIBS)
EXE 	:= main.out
DEB 	:= debug.out
SRC 	:= ./src
SRCS 	:= $(wildcard $(SRC)/*.c)
OBJ 	:= ./obj
OBJS 	:= $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
TDIR 	:= ./testdir

.PHONY: all clean test1 test2 test3

all: $(EXE)

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(DEB): $(OBJS) 
	$(CC) -g $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -MF $(OBJ)/$*.d -o $@ -c $<

-include $(OBJ)/*.d

test1: $(EXE)
	./$(EXE) $(TDIR) 1 5

test2: $(EXE)
	./$(EXE) $(TDIR) 5 1

test3: $(EXE)
	./$(EXE) $(TDIR) 5 5

clean:
	rm -fr $(EXE) $(DEB) $(OBJ)
