CC=gcc
CFLAGS=-Wall -Werror
OPT=-O0
INCLUDES=.
LIBDIR=.
LIBRARIES=
SOURCES=main.c

all:
	@$(CC) \
		$(CFLAGS) \
		$(OPT) \
		$(foreach X,$(INCLUDES),-I$(X)) \
		$(foreach X,$(LIBRARIES),-l$(X)) \
		$(foreach X,$(LIBDIR),-L$(X)) \
		$(SOURCES)

clean:
	rm -rf a.out main.o
