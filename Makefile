CC = g++
CFLAG = -Wall -Wextra
EXE = bmp
OBJ = main.cpp Facade.cpp AI.cpp Board.cpp Engine.cpp
DEPS = Facade.h Board.h AI.h Engine.h

all: $(EXE)
	
build: $(EXE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE) -lm

run:
	@./bmp

.PHONY: clean

clean:
	rm -f *.o $(EXE)
