# Copyright (c) 2019 Yanyi Hu, under the MIT License
# Target
exe := traSH
objects := main.o
obj_dir := obj
src_dir := src

all: $(obj_dir) $(exe)

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

# create temp directory
$(obj_dir):
	@echo "MKDIR $@"
	$(Q)mkdir -p $(obj_dir)

# final executable
$(exe): $(obj_dir)/$(objects)
	@echo "LD    $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $<

# objects
$(obj_dir)/%.o: $(src_dir)/%.c
	@echo "CC    $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo "CLEAN"
	$(Q)rm -rf core $(exe) $(obj_dir)