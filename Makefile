
CC = g++

# SFML = D:/SFML-2.5.1
SFML = D:/libs/sfml_2.5.1

CFLAGS = -DSFML_STATIC

INCLUDE = -I"./include"
LIBS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype

#==============================================================================

# platform-dependant flags

ifeq ($(OS), Windows_NT)
	CFLAGS += -L'${SFML}/lib'
	CFLAGS += -I'${SFML}/include'
	EXEC = game.exe

	RM = del /Q /S *.exe *.o
else
	EXEC = ./game

	RM = rm -f *.o; rm -f game
endif

all: \
src/frameclock.o \
src/block.o \
src/board.o \
src/main.o
	$(CC) $^ -o game $(CFLAGS) $(LIBS)

src/main.o: \
include/entity.h \
include/block.h \
include/text.h \
include/frameclock.h

src/frameclock.o: include/frameclock.h

src/block.o: include/block.h include/constants.h

src/board.o: include/board.h include/constants.h

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

#==============================================================================
# utility rules
#==============================================================================

.PHONY: run clean

run: all
	$(EXEC)

clean:
	$(RM)
