CXX=g++
CXXFLAGS=-std=c++14 -MMD -g -Werror
OBJECTS= player.o cell.o pawn.o bishop.o knight.o rook.o queen.o king.o empty.o nullcell.o chessboard.o textdisplay.o window.o graphicsdisplay.o strategy.o level1.o level2.o level3.o level4.o main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess -lX11

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
