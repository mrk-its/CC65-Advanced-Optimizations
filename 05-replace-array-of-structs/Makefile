CL65_OPTIMIZATION_FLAGS=-Osir -Cl

all:	game.xex

run:	game.xex
	atari800 -run game.xex

clean:
	-rm game.xex
	-rm game.lst
	-rm game.lbl
	-rm game.o

game.xex game.lst game.lbl game.o: game.c
	cl65 -I../utils/cc65/ ${CL65_OPTIMIZATION_FLAGS} -t atari -Ln game.lbl --listing game.lst --add-source -o game.xex game.c
