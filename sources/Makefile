# tools
CC := gcc -m32
RM := rm -f

# flags
CFLAGS := -O0 -ggdb -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack
LDFLAGS := -ggdb -fno-stack-protector -z execstack
LDLIBS :=
MODERNCFLAGS := -fcf-protection=none -mno-shstk -fno-pic -fno-pie -fno-inline-small-functions
MODERNLDFLAGS := -no-pie
CFLAGS += $(MODERNCFLAGS)
LDFLAGS += $(MODERNLDFLAGS)
# sources
sources := target0.c target1.c target2.c target3.c target4.c target5.c \
           target6.c target7.c tmalloc.c
targets := target1 target2 target3 target4 target5 target6 target7 target0 target8

# gmake magic
.PHONY: default all clean

#targets
default: all
all: $(targets)

clean:
	$(RM) $(targets) $(sources:.c=.o)

# special make process for eip target
target3:    CFLAGS += -fomit-frame-pointer -O2

# special make process for target8 Ret2libc
target8: target8.c
	$(CC) -ggdb -fno-stack-protector -mpreferred-stack-boundary=2 $(MODERNCFLAGS) target8.c -o target8

#dependencies
target5: tmalloc.o
tmalloc.o target5.o: tmalloc.h
