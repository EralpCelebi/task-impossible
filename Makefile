BINFILES := ./main
AUXFILES := valgrind.rpt README.md
SRCFILES := $(shell find -name "*.c")
HDRFILES := $(shell find -name "*.h")
DEPFILES := $(SRCFILES:.c=.d)
OBJFILES := $(SRCFILES:.c=.o)

CFLAGS ?= -O0 -g
CFLAGS += -Wall -Wextra -MMD -MP -Iinclude

LDFLAGS ?=
LDFLAGS +=

all: $(BINFILES)

check: $(BINFILES)
	valgrind --leak-check=yes --log-file=valgrind.rpt $(BINFILES)

clean:
	$(RM) $(BINFILES) $(OBJFILES) $(AUXFILES) $(DEPFILES)

$(BINFILES): $(OBJFILES)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPFILES)
