LIBCPPSIM=$(LIBCPPSIM_ROOT)/src/libcppsim.a
LIBCPPSIM_HEADERS=$(LIBCPPSIM_ROOT)/src/
STD=-std=c++14
CPP=g++
CFLAGS=$(STD) -g -Wall -Werror -Wextra -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -I$(LIBCPPSIM_HEADERS) -Wno-unused-parameter
EXEC=simulator


SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o) pe/pe.o cpu/cpu.o metric/metric.o common/common.o mobile/mobile.o
OBJS_NO_MAIN=pe/pe.o cpu/cpu.o metric/metric.o common/common.o mobile/mobile.o
HEADERS=$(SRCS:.cpp=.hpp)

all: test

test: $(OBJS_NO_MAIN) test.cpp Source.o
	@echo [CPP] test.o
	@g++ -c $(CFLAGS) -DTEST test.cpp -o test.o
	@echo [CPP] $@
	@g++ $(CFLAGS) $(OBJS_NO_MAIN) Source.o test.o $(LIBCPPSIM) -o test

simulador: $(OBJS)
	@echo [CPP] $@
	@g++ $(CFLAGS) $(OBJS) $(LIBCPPSIM) -o $(EXEC)

%.o: %.cpp %.hpp 
	@echo [CPP] $@
	@g++ $(CFLAGS) -c $< -o $@

pe/pe.o: $(wildcard pe/*.cpp) $(wildcard pe/*.hpp)
	make -C pe

cpu/cpu.o: $(wildcard cpu/*.cpp) $(wildcard cpu/*.hpp)
	make -C cpu

mobile/mobile.o: $(wildcard mobile/*.cpp) $(wildcard mobile/*.hpp)
	make -C mobile

metric/metric.o: $(wildcard metric/*.cpp) $(wildcard metric/*.hpp)
	make -C metric

common/common.o: $(wildcard common/*.cpp) $(wildcard common/*.hpp)
	make -C common

clean:
	rm -f *.o $(EXEC)
	cd pe && make clean
	cd cpu && make clean
	cd mobile && make clean
	cd metric && make clean
	cd common && make clean
