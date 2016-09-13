LIBCPPSIM=$(LIBCPPSIM_ROOT)/src/libcppsim.a
LIBCPPSIM_HEADERS=$(LIBCPPSIM_ROOT)/src/
STD=-std=c++14
CPP=g++
CFLAGS=$(STD) -Wall -Werror -Wextra -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -I$(LIBCPPSIM_HEADERS) -Wno-unused-parameter
EXEC=simulator

OBJS=main.o Source.o pe/pe.o cpu/cpu.o

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o) pe/pe.o cpu/cpu.o
HEADERS=$(SRCS:.cpp=.hpp)

all: simulador

simulador: $(OBJS)
	g++ $(CFLAGS) $(OBJS) $(LIBCPPSIM) -o $(EXEC)

%.o: %.cpp %.hpp 
	gcc $(CFLAGS) -c $< -o $@

pe/pe.o:
	make -C pe

cpu/cpu.o:
	make -C cpu

mobile/mobile.o:
	make -C mobile


clean:
	rm -f *.o $(EXEC)
	cd pe && make clean
	cd cpu && make clean
	cd mobile && make clean

test:
	./$(EXEC)
