LIBCPPSIM=$(LIBCPPSIM_ROOT)/src/libcppsim.a
LIBCPPSIM_HEADERS=$(LIBCPPSIM_ROOT)/src/
STD=-std=c++14
OBJS=main.o
CPP=g++
CFLAGS=$(STD) -Wall -Werror -Wextra -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -I$(LIBCPPSIM_HEADERS)
EXEC=simulator


all: simulador


simulador: $(OBJS)
	g++ $(CFLAGS) $(OBJS) $(LIBCPPSIM) -o $(EXEC)

main.o: main.cpp
	$(CPP) -c $(STD) $(CFLAGS) main.cpp -o main.o


clean:
	rm -f *.o $(EXEC)

test:
	./$(EXEC)
