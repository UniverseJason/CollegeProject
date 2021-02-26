# Define the machine object files for your program
OBJECTS = ycy354Project1.o Stack.o
# Define your include file
INCLUDES = Stack.h

# make for the executable
project1: ${OBJECTS}
	gcc -g -o project1 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
