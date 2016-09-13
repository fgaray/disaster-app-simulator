SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
HEADERS=$(SRCS:.cpp=.hpp)

LIBCPPSIM_HEADERS=$(LIBCPPSIM_ROOT)/src/
CFLAGS=$(STD) -Wall -Wextra -Werror -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -I$(LIBCPPSIM_HEADERS) -Wno-unused-parameter

all: pe.o

pe.o: $(OBJS)
	ld -r $(OBJS) -o pe.o

%.o: %.cpp %.hpp 
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
