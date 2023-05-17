/* SPDX-License-Identifier: GPL-2.0-only
 *
 * Makefile with executable name myprogram
 *
 * Copyright (C) 2023 Samsung Electronics Co., Ltd.
 *
 * Author: Hrushikesh Reddy Mudhireddy  (h.mudhireddy)
 */
 

CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -ludev  

# List of source files
SRCS = usb_manager.c monitor.c list.c export.c 
# Generate corresponding object file names
OBJS = $(SRCS:.c=.o)

# The target executable
TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)


