CC=gcc
CFLAGS=-Wall -Werror -O0
INCLUDES=.
LIBDIR=.
LIBRARIES=
SOURCES=main.c
DEPENDENCIES=$(SOURCES:.c=.d)
OBJECTS=$(SOURCES:.c=.o)
BIN=a.out

all: $(OBJECTS)
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

clean:
	@echo "Removing build results"
	@rm -f $(DEPENDENCIES) $(OBJECTS) $(BIN)
