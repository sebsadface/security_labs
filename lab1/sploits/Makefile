# tools
CC := gcc -m32
RM := rm -f

# flags
CFLAGS := -ggdb
LDFLAGS :=
LDLIBS :=

# sources
sources := sploit0.c sploit1.c sploit2.c sploit3.c sploit4.c sploit5.c sploit6.c sploit7.c sploit8.c
targets := $(sources:.c=)

# gmake magic
.PHONY: default all clean

#targets
default: all
all: $(targets)

clean:
	$(RM) $(targets) $(sources:.c=.o)

#dependencies
$(sources:.c=.o): shellcode.h
