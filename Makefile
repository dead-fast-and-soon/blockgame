
CC = g++

ifeq ($(OS), Windows_NT)
	WIN_FLAGS += -L'D:/SFML-2.5.1/lib'
	WIN_FLAGS += -I'D:/SFML-2.5.1/include'
	# WIN_FLAGS += -L'D:/libs/sfml_2.5.1/lib'
	# WIN_FLAGS += -I'D:/libs/sfml_2.5.1/include'
	EXEC = game.exe

	RM = del /Q /S *.exe *.o
else
	WIN_FLAGS=
	EXEC = ./game

	RM = rm -f *.o; rm -f game
endif

CFLAGS = -DSFML_STATIC

INCLUDE = -I"./include"
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: \
src/frameclock.o \
src/block.o \
src/board.o \
src/main.o
	$(CC) $^ -o game $(CFLAGS) $(WIN_FLAGS) $(LIBS)

src/main.o: \
include/entity.h \
include/block.h \
include/text.h \
include/frameclock.h

src/frameclock.o: include/frameclock.h

src/block.o: include/block.h include/constants.h

src/board.o: include/board.h include/constants.h

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS) $(WIN_FLAGS)

.PHONY: run clean

run: all
	$(EXEC)

clean:
	$(RM)
