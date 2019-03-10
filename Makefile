# Copyright (c) 2019 Yanyi Hu, under the MIT License
# Target
exe := traSH
obj := main.o

all := $(exe)

# Compiler
CC := gcc

# CC flags
CFLAGS := -Wall -Werror

ifneq ($(V),1)
Q = @
endif

ifneq ($(D), 1)
CFLAGS += -O2
else
CFLAGS += -g
CFLAGS += -O0
endif

$(exe): $(obj)
	@echo "LD $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $<

# objects
%.o: %.c
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo "CLEAN"
	$(Q)rm -f core $(exe) *.o