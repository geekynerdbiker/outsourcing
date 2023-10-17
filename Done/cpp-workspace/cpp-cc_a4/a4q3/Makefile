CXX = g++
CXXFLAGS = -std=c++14 -MMD -Werror=vla -Wall -Wextra -Wpedantic -g
EXEC = a4q3
OBJECTS = main.o cell.o subject.o textdisplay.o grid.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
