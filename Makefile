DEBUG = -g -DMOVES_ROOK_DEBUG_disabled

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

eval.o:
	gcc $(DEBUG) -c eval.c

search.o:
	gcc $(DEBUG) -c search.c

xboard.o:
	gcc $(DEBUG) -c xboard.c

bitboardTester: bitboard.o bitboards.o bitboardTester.c
	gcc $(DEBUG) -o bitboardTester bitboardTester.c bitboard.o bitboards.o

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

gchess: main.c boardstate.o game_state.o util.h \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o xboard.o search.o eval.o
	gcc $(DEBUG) -o gchess main.c boardstate.o game_state.o \
	enumerate_moves.o moves.o bitboards.o bitboard.o bitboard_list.o move.o \
	game_state_list.o xboard.o search.o eval.o

get_corner_halves: get_corner_halves.c bitboard.o
	gcc $(DEBUG) -o get_corner_halves get_corner_halves.c bitboard.o

tags: 
	etags -d --declarations *.c *.h

clean:
	rm -rf *.o

depend:
	makedepend *.c *.h

# DO NOT DELETE

bitboard.o: position.h bitboards.h bitboard.h /usr/include/stdio.h
bitboard.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
bitboard.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
bitboardTester.o: bitboard.h position.h bitboards.h /usr/include/stdio.h
bitboardTester.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
bitboardTester.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
bitboard_list.o: bitboard.h position.h bitboard_list.h /usr/include/stdlib.h
bitboard_list.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
bitboard_list.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
bitboard_list.o: /usr/include/string.h /usr/include/strings.h
bitboards.o: bitboards.h bitboard.h position.h
boardstate.o: boardstate.h bitboard.h position.h util.h move.h piece.h
boardstate.o: bitboard_list.h bitboards.h /usr/include/string.h
boardstate.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
boardstate.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
boardstate.o: /usr/include/strings.h
boardstateTester.o: boardstate.h bitboard.h position.h util.h move.h piece.h
boardstateTester.o: bitboard_list.h /usr/include/stdio.h
boardstateTester.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
boardstateTester.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
consoleGame.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
consoleGame.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
consoleGame.o: /usr/include/machine/_types.h /usr/include/stdio.h
consoleGame.o: enumerate_moves.h game_state.h boardstate.h bitboard.h
consoleGame.o: position.h util.h move.h piece.h bitboard_list.h
consoleGame.o: game_state_list.h
enumerate_moves.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
enumerate_moves.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
enumerate_moves.o: /usr/include/machine/_types.h boardstate.h bitboard.h
enumerate_moves.o: position.h util.h move.h piece.h bitboard_list.h
enumerate_moves.o: game_state.h game_state_list.h enumerate_moves.h moves.h
enumerate_moves.o: bitboards.h
enumerate_movesTester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
enumerate_movesTester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
enumerate_movesTester.o: /usr/include/machine/_types.h enumerate_moves.h
enumerate_movesTester.o: game_state.h boardstate.h bitboard.h position.h
enumerate_movesTester.o: util.h move.h piece.h bitboard_list.h
enumerate_movesTester.o: game_state_list.h bitboards.h
eval.o: eval.h game_state.h boardstate.h bitboard.h position.h util.h move.h
eval.o: piece.h bitboard_list.h game_state_list.h
game_state.o: game_state_list.h game_state.h boardstate.h bitboard.h
game_state.o: position.h util.h move.h piece.h bitboard_list.h
game_state.o: enumerate_moves.h /usr/include/stdio.h /usr/include/sys/cdefs.h
game_state.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
game_state.o: /usr/include/machine/_types.h /usr/include/stdlib.h
game_state_list.o: game_state_list.h game_state.h boardstate.h bitboard.h
game_state_list.o: position.h util.h move.h piece.h bitboard_list.h
game_state_list.o: /usr/include/stdlib.h /usr/include/sys/cdefs.h
game_state_list.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
game_state_list.o: /usr/include/machine/_types.h
game_state_tester.o: enumerate_moves.h game_state.h boardstate.h bitboard.h
game_state_tester.o: position.h util.h move.h piece.h bitboard_list.h
game_state_tester.o: game_state_list.h bitboards.h /usr/include/stdio.h
game_state_tester.o: /usr/include/sys/cdefs.h /usr/include/sys/_null.h
game_state_tester.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
get_corner_halves.o: bitboard.h position.h
main.o: /usr/include/unistd.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/types.h /usr/include/machine/endian.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/sys/_pthreadtypes.h /usr/include/sys/select.h
main.o: /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h
main.o: /usr/include/sys/timespec.h /usr/include/sys/unistd.h
main.o: /usr/include/sys/_null.h
move.o: move.h piece.h boardstate.h bitboard.h position.h util.h
move.o: bitboard_list.h
moves.o: moves.h move.h piece.h game_state.h boardstate.h bitboard.h
moves.o: position.h util.h bitboard_list.h game_state_list.h bitboards.h
moves.o: enumerate_moves.h
movesTester.o: moves.h move.h piece.h game_state.h boardstate.h bitboard.h
movesTester.o: position.h util.h bitboard_list.h game_state_list.h
movesTester.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
movesTester.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
movesTester.o: /usr/include/machine/_types.h
search.o: search.h game_state.h boardstate.h bitboard.h position.h util.h
search.o: move.h piece.h bitboard_list.h game_state_list.h enumerate_moves.h
search.o: eval.h
test_array.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
test_array.o: /usr/include/sys/_null.h /usr/include/sys/_types.h
test_array.o: /usr/include/machine/_types.h
xboard.o: xboard.h game_state.h boardstate.h bitboard.h position.h util.h
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
bitboard.o: position.h
bitboards.o: bitboard.h position.h
boardstate.o: bitboard.h position.h util.h move.h piece.h bitboard_list.h
enumerate_moves.o: game_state.h boardstate.h bitboard.h position.h util.h
enumerate_moves.o: move.h piece.h bitboard_list.h game_state_list.h
eval.o: game_state.h boardstate.h bitboard.h position.h util.h move.h piece.h
eval.o: bitboard_list.h game_state_list.h
game_state.o: boardstate.h bitboard.h position.h util.h move.h piece.h
game_state.o: bitboard_list.h game_state_list.h game_state.h
game_state_list.o: game_state.h boardstate.h bitboard.h position.h util.h
game_state_list.o: move.h piece.h bitboard_list.h game_state_list.h
move.o: piece.h
moves.o: move.h piece.h game_state.h boardstate.h bitboard.h position.h
moves.o: util.h bitboard_list.h game_state_list.h
search.o: game_state.h boardstate.h bitboard.h position.h util.h move.h
search.o: piece.h bitboard_list.h game_state_list.h
