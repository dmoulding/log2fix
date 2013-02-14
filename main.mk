CFLAGS     := -g -O2 -pipe -Wall -Werror
TARGET     := tester
TGT_LDLIBS := -lm

SRC_CFLAGS := -std=c99

SOURCES := \
    log2fix.c \
    main.c
