CC 		:= gcc
FLAGS 	:= -Wall -pedantic
EXE 	:= mybc.out
SRC 	:= ./src
SRCS 	:= $(wildcard $(SRC)/*.c)
OBJ 	:= ./obj
OBJS 	:= $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

.PHONY: all clean


all: $(EXE) 

struct:
	./structure.sh
	echo $(SRCS)

$(EXE): $(OBJS) 
	$(CC) $(FLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(FLAGS) -o $@ -c $?

clean:
	rm -f $(EXE) $(OBJS)
