DEBUG = -g -DMOVES_ROOK_DEBUG_disabled

OBJ_FILES = bitboard.o boardstate.o move.o game_state.o moves.o \
	bitboards.o enumerate_moves.o bitboard_list.o game_state_list.o \
	positions.o position_list.o eval.o search.o xboard.o position.o

bitboard.o: 
	gcc $(DEBUG) -c bitboard.c

boardstate.o: 
	gcc $(DEBUG) -c boardstate.c

move.o: 
	gcc $(DEBUG) -c move.c

game_state.o: 
	gcc $(DEBUG) -c game_state.c

moves.o: 
	gcc $(DEBUG) -c moves.c

bitboards.o:
	gcc $(DEBUG) -c bitboards.c

enumerate_moves.o:
	gcc $(DEBUG) -c enumerate_moves.c

bitboard_list.o:
	gcc $(DEBUG) -c bitboard_list.c

game_state_list.o:
	gcc $(DEBUG) -c game_state_list.c

position.o:
	gcc $(DEBUG) -c position.c

positions.o:
	gcc $(DEBUG) -c positions.c

position_list.o:
	gcc $(DEBUG) -c position_list.c

eval.o:
	gcc $(DEBUG) -c eval.c

search.o:
	gcc $(DEBUG) -c search.c

xboard.o:
	gcc $(DEBUG) -c xboard.c

bitboardTester: bitboard.o bitboards.o bitboardTester.c
	gcc $(DEBUG) -o bitboardTester bitboardTester.c bitboard.o bitboards.o

positions_tester.o: 
	gcc $(DEBUG) -c positions_tester.c

positions_tester: positions_tester.o positions.o bitboard.o position_list.o \
	bitboard.o bitboards.o position.o
	gcc $(DEBUG) -o positions_tester positions_tester.o positions.o bitboard.o \
		position_list.o bitboards.o position.o

boardstateTester: boardstate.o boardstateTester.c bitboard.o bitboards.o move.o bitboard_list.o
	gcc $(DEBUG) -o boardstateTester bitboard.o boardstate.o boardstateTester.c \
		bitboards.o move.o bitboard_list.o

game_state_tester: boardstate.o game_state_tester.c game_state.o bitboard.o bitboards.o move.o \
	bitboard_list.o game_state_list.o enumerate_moves.o moves.o
	gcc $(DEBUG) -o game_state_tester game_state_tester.c boardstate.o game_state.o \
	bitboard.o bitboards.o move.o bitboard_list.o game_state_list.o \
	enumerate_moves.o moves.o

movesTester: moves.o util.h move.o game_state.o movesTester.c bitboard_list.o \
	bitboards.o boardstate.o bitboard.o
	gcc $(DEBUG) -o movesTester game_state.o boardstate.o \
	moves.o move.o bitboard.o movesTester.c bitboard_list.o bitboards.o

enumerate_movesTester: enumerate_movesTester.c boardstate.o game_state.o util.h \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o
	gcc $(DEBUG) -o enumerate_movesTester enumerate_movesTester.c boardstate.o game_state.o \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o

consoleGame: consoleGame.c boardstate.o game_state.o util.h \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o
	gcc $(DEBUG) -o consoleGame consoleGame.c boardstate.o game_state.o \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o

gchess: main.c $(OBJ_FILES)
	gcc $(DEBUG) -o gchess main.c $(OBJ_FILES)

get_corner_halves: get_corner_halves.c bitboard.o
	gcc $(DEBUG) -o get_corner_halves get_corner_halves.c bitboard.o

tags: 
	etags -d --declarations *.c *.h

clean:
	rm -rf *.o

depend:
	makedepend *.c *.h

# DO NOT DELETE

bitboard.o: position.h bitboards.h bitboard.h types.h /usr/include/stdio.h
bitboard.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
bitboard.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
bitboardTester.o: bitboard.h position.h types.h bitboards.h
bitboardTester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bitboardTester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
bitboardTester.o: /usr/include/machine/_types.h
bitboard_list.o: bitboard.h position.h types.h bitboard_list.h
bitboard_list.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
bitboard_list.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
bitboard_list.o: /usr/include/machine/_types.h /usr/include/string.h
bitboard_list.o: /usr/include/strings.h
bitboards.o: bitboards.h bitboard.h position.h types.h
boardstate.o: boardstate.h bitboard.h position.h types.h move.h piece.h
boardstate.o: bitboard_list.h bitboards.h /usr/include/string.h
boardstate.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
boardstate.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
boardstate.o: /usr/include/strings.h
boardstateTester.o: boardstate.h bitboard.h position.h types.h move.h piece.h
boardstateTester.o: bitboard_list.h /usr/include/stdio.h
boardstateTester.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
boardstateTester.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
consoleGame.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
consoleGame.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
consoleGame.o: /usr/include/machine/_types.h /usr/include/stdio.h
consoleGame.o: enumerate_moves.h game_state.h boardstate.h bitboard.h
consoleGame.o: position.h types.h move.h piece.h bitboard_list.h
consoleGame.o: game_state_list.h
enumerate_moves.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
enumerate_moves.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
enumerate_moves.o: /usr/include/machine/_types.h boardstate.h bitboard.h
enumerate_moves.o: position.h types.h move.h piece.h bitboard_list.h
enumerate_moves.o: game_state.h game_state_list.h enumerate_moves.h moves.h
enumerate_moves.o: bitboards.h
enumerate_movesTester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
enumerate_movesTester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
enumerate_movesTester.o: /usr/include/machine/_types.h enumerate_moves.h
enumerate_movesTester.o: game_state.h boardstate.h bitboard.h position.h
enumerate_movesTester.o: types.h move.h piece.h bitboard_list.h
enumerate_movesTester.o: game_state_list.h bitboards.h
eval.o: eval.h game_state.h boardstate.h bitboard.h position.h types.h move.h
eval.o: piece.h bitboard_list.h game_state_list.h
game_state.o: game_state_list.h game_state.h boardstate.h bitboard.h
game_state.o: position.h types.h move.h piece.h bitboard_list.h
game_state.o: enumerate_moves.h /usr/include/stdio.h /usr/include/sys/cdefs.h
game_state.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
game_state.o: /usr/include/machine/_types.h /usr/include/stdlib.h
game_state_list.o: game_state_list.h game_state.h boardstate.h bitboard.h
game_state_list.o: position.h types.h move.h piece.h bitboard_list.h
game_state_list.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
game_state_list.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
game_state_list.o: /usr/include/machine/_types.h
game_state_tester.o: enumerate_moves.h game_state.h boardstate.h bitboard.h
game_state_tester.o: position.h types.h move.h piece.h bitboard_list.h
game_state_tester.o: game_state_list.h bitboards.h /usr/include/stdio.h
game_state_tester.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
game_state_tester.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
get_corner_halves.o: bitboard.h position.h types.h
main.o: /usr/include/unistd.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/types.h /usr/include/machine/endian.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/sys/_pthreadtypes.h /usr/include/sys/select.h
main.o: /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h
main.o: /usr/include/sys/timespec.h /usr/include/sys/unistd.h
main.o: /usr/include/sys/_null.h
move.o: move.h piece.h boardstate.h bitboard.h position.h types.h
move.o: bitboard_list.h
moves.o: moves.h move.h piece.h game_state.h boardstate.h bitboard.h
moves.o: position.h types.h bitboard_list.h game_state_list.h bitboards.h
moves.o: enumerate_moves.h
movesTester.o: moves.h move.h piece.h game_state.h boardstate.h bitboard.h
movesTester.o: position.h types.h bitboard_list.h game_state_list.h
movesTester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
movesTester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
movesTester.o: /usr/include/machine/_types.h
position.o: position.h
position_list.o: position.h position_list.h /usr/include/stdlib.h
position_list.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
position_list.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
positions.o: positions.h position_list.h /usr/include/stdlib.h
positions.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
positions.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
positions.o: position.h types.h
positions_tester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
positions_tester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
positions_tester.o: /usr/include/machine/_types.h positions.h position_list.h
positions_tester.o: /usr/include/stdlib.h position.h bitboard.h types.h
search.o: search.h game_state.h boardstate.h bitboard.h position.h types.h
search.o: move.h piece.h bitboard_list.h game_state_list.h enumerate_moves.h
search.o: eval.h
xboard.o: xboard.h game_state.h boardstate.h bitboard.h position.h types.h
xboard.o: move.h piece.h bitboard_list.h game_state_list.h enumerate_moves.h
xboard.o: search.h /usr/include/signal.h /usr/include/sys/cdefs.h
xboard.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
xboard.o: /usr/include/sys/signal.h /usr/include/sys/_sigset.h
xboard.o: /usr/include/machine/signal.h /usr/include/machine/trap.h
xboard.o: /usr/include/stdio.h /usr/include/sys/_null.h /usr/include/unistd.h
xboard.o: /usr/include/sys/types.h /usr/include/machine/endian.h
xboard.o: /usr/include/sys/_pthreadtypes.h /usr/include/sys/select.h
xboard.o: /usr/include/sys/_timeval.h /usr/include/sys/timespec.h
xboard.o: /usr/include/sys/unistd.h /usr/include/string.h
xboard.o: /usr/include/strings.h /usr/include/stdlib.h
bitboard.o: position.h types.h
bitboards.o: bitboard.h position.h types.h
boardstate.o: bitboard.h position.h types.h move.h piece.h bitboard_list.h
enumerate_moves.o: game_state.h boardstate.h bitboard.h position.h types.h
enumerate_moves.o: move.h piece.h bitboard_list.h game_state_list.h
eval.o: game_state.h boardstate.h bitboard.h position.h types.h move.h
eval.o: piece.h bitboard_list.h game_state_list.h
game_state.o: boardstate.h bitboard.h position.h types.h move.h piece.h
game_state.o: bitboard_list.h game_state_list.h game_state.h
game_state_list.o: game_state.h boardstate.h bitboard.h position.h types.h
game_state_list.o: move.h piece.h bitboard_list.h game_state_list.h
move.o: piece.h
moves.o: move.h piece.h game_state.h boardstate.h bitboard.h position.h
moves.o: types.h bitboard_list.h game_state_list.h
position_list.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
position_list.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
position_list.o: /usr/include/machine/_types.h position.h
positions.o: position_list.h /usr/include/stdlib.h /usr/include/sys/cdefs.h
positions.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
positions.o: /usr/include/machine/_types.h position.h
search.o: game_state.h boardstate.h bitboard.h position.h types.h move.h
search.o: piece.h bitboard_list.h game_state_list.h
