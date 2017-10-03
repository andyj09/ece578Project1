# Project1
CC=g++
CFLAGS=-std=c++11 -c -Wall
#LDFLAGS=
INCLUDES=-Iinclude
# Note the order of source files
SOURCES=MainProgram.cpp Station.cpp TimelineSlots.cpp
# Substitution of file endings
# All strings in SOURCES with ending of .cpp is substituted by .o
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project1.o

# Default make option
all: $(SOURCES) $(EXECUTABLE)

# Note the position of LDFLAGS    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) $(INCLUDES) -o $@

# Double-suffix .cpp.o is equivalent to %.o: %.cpp
# .cpp is the first prerequisite and .o is the target
# Automatic variable $< refers to the first prerequisite, i.e. .cpp file
# Automatic variable $@ refers to the target, i.e. .o file    
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(OBJECTS) $(DEPS) $(EXECUTABLE)
