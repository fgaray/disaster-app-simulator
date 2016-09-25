SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
HEADERS=$(SRCS:.cpp=.hpp)

LIBCPPSIM_HEADERS=$(LIBCPPSIM_ROOT)/src/
CFLAGS=$(STD) -Wall -Wextra -Werror -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -I$(LIBCPPSIM_HEADERS) -Wno-unused-parameter

all: metric.o

metric.o: $(OBJS)
	@echo [LD] $(OBJS)
	@ld -r $(OBJS) -o metric.o

%.o: %.cpp %.hpp 
	@echo [CPP] $@
	@g++ $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
