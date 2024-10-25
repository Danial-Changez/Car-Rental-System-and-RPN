# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror

# Source files
a1_SRCS = q1.c q1_functions.c
a2_SRCS = q2.c q2_functions.c

# Header files
HEADERS = q1.h q2.h

# Object files
a1_OBJS = $(a1_SRCS:.c=.o)
a2_OBJS = $(a2_SRCS:.c=.o)

# Executable name
a1_TARGET = a2q1
a2_TARGET = a2q2

# Build target
all: $(a1_TARGET) $(a2_TARGET)

# Link object files to create the executable for assignment 1
$(a1_TARGET): $(a1_OBJS)
	$(CC) $(CFLAGS) -o $@ $(a1_OBJS)

# Link object files to create the executable for assignment 2
$(a2_TARGET): $(a2_OBJS)
	$(CC) $(CFLAGS) -o $@ $(a2_OBJS)

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Clean target
clean:
	rm -f $(a1_TARGET) $(a2_TARGET) *.o
