CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3


INCLUDES = $(shell echo *.h)
EXECS    = MetroSim

MetroSim: main.o MetroSim.o  
	${CXX} ${LDFLAGS} $^ -o $@ 


%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c -o $@ $<

.PHONY: clean
clean:
	rm -f ${EXECS} *.o *.dSYM./

