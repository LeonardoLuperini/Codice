CC 		:= gcc
CFLAGS 	:= -Wall -Wextra -pedantic -std=c11
CPPFLAGS:= -pthread
LDLIBS  := -lrt -lm
LDFLAGS := -pthread $(LDLIBS)
EXE 	:= main.out
DEB 	:= debug.out
SRC 	:= ./src
SRCS 	:= $(wildcard $(SRC)/*.c)
OBJ 	:= ./obj
OBJS 	:= $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)


.DELETE_ON_ERROR:
.PHONY: all clean test1 test2 test3 test4 test5

all: $(EXE)

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(DEB): $(OBJS) 
	$(CC) -g $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -MF $(OBJ)/$*.d -o $@ -c $<

-include $(OBJ)/*.d

run: $(EXE)
	./$(EXE)

# target che esegue test 1
test1: $(EXE)
	./$(EXE) 3 file0.dat 0 >output1.txt
	@echo risultato corretto: 0 primi, checksum 0

# target che esegue test 2
test2: $(EXE)
	./$(EXE) 5  file10.dat 10 >output2.txt
	@echo  risultato corretto: 2 primi, checksum 50113667

# target che esegue test 3
test3: $(EXE)
	./$(EXE) 3 file1000.dat 1000 >output3.txt
	@echo risultato corretto: 57 primi, checksum 2271174463100

# target che esegue test 4
test4: $(EXE)
	./$(EXE) 10 file100000.dat 100000 >output4.txt
	@echo risultato corretto: 4876 primi, checksum 16643429447169186

# target che esegue test 5
test5: $(EXE)
	./$(EXE) 2 file100000.dat 100000 >output5.txt &
	pkill -INT $(EXE)
	pkill -INT $(EXE)
	@echo risultato corretto: 4876 primi, checksum 16643429447169186

clean:
	rm -fr $(EXE) $(DEB) $(OBJ)
