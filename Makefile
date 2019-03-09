# Copyright (c) 2019 Yanyi Hu, under the MIT License
# Target
exe := fshell

# Target method
all:

# Compiler
CC := gcc

# CC flags
CFLAGS := -Wall -Werror -pipe
CDEPF = -MMD -MF $(@:.o=.d)

# Makefile Debug
ifneq ($(V),1)
Q = @
endif
# Debug flags
ifneq ($(D), 1)
CFLAGS += -O2
else
CFLAGS += -g
CFLAGS += -O0
CFLAGS += -D LIBFS_DEBUG
endif
