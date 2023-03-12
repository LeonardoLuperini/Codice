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

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(DEB): $(OBJS) 
	$(CC) -g $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -MF $(OBJ)/$*.d -o $@ -c $<

-include $(OBJ)/*.d

clean:
	rm -fr $(EXE) $(DEB) $(OBJ)
