CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = a4q4
OBJECTS = main.o grid.o cell.o subject.o observer.o state.o textdisplay.o info.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
