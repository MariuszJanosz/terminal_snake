CC=gcc
CFLAGS=-Wall -Werror -O0 -g
INCLUDES=.
LIBDIR=.
LIBRARIES=
SOURCES=$(wildcard *.c)
DEPENDENCIES=$(SOURCES:.c=.d)
OBJECTS=$(SOURCES:.c=.o)
BIN=a.out

.PHONY: all

all: $(BIN)

$(BIN): $(OBJECTS)
	@echo "Building $(BIN)"
	@$(CC) \
		$(CFLAGS) \
		$(OPT) \
		$(foreach X,$(LIBDIR),-L$(X)) \
		$(foreach X,$(LIBRARIES),-l$(X)) \
		$(OBJECTS) \
		-o $(BIN)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) \
		-c \
		$(CFLAGS) \
		-MMD \
		$(OPT) \
		$(foreach X,$(INCLUDES),-I$(X)) \
		$< \
		-o $@

-include $(DEPENDENCIES)

.PHONY: clean

clean:
	@echo "Removing build results"
	@rm -f $(DEPENDENCIES) $(OBJECTS) $(BIN)
