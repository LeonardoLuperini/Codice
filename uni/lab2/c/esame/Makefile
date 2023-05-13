CC 		:= gcc
CFLAGS 	:= -Wall -Wextra -pedantic
CPPFLAGS:= -pthread
LDLIBS  := -lm -lrt
LDFLAGS := -pthread $(LDLIBS)

EXE 	:= main.out
DEB 	:= debug.out

SRC 	:= ./src
SRCS 	:= $(wildcard $(SRC)/*.c)
RELFOL	:= ./relobj
DEBFOL	:= ./debobj
RELOBJS	:= $(SRCS:$(SRC)/%.c=$(RELFOL)/%.o)
DEBOBJS	:= $(SRCS:$(SRC)/%.c=$(DEBFOL)/%.o)

.PHONY: all clean deb

all: $(EXE)

$(EXE): $(RELOBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(RELFOL)/%.o: $(SRC)/%.c
	@mkdir -p $(RELFOL)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -MF $(RELFOL)/$*.d -o $@ -c $<

-include $(RELFOL)/*.d

deb: $(DEB)

$(DEB): $(DEBOBJS) 
	$(CC) -g -DDEBUG $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(DEBFOL)/%.o: $(SRC)/%.c
	@mkdir -p $(DEBFOL)
	$(CC) -g -DDEBUG $(CFLAGS) $(CPPFLAGS) -MMD -MP -MF $(DEBFOL)/$*.d -o $@ -c $<

-include $(DEBFOL)/*.d

clean:
	rm -fr $(EXE) $(DEB) $(RELFOL) $(DEBFOL)
