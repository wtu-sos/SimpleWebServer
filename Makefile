HEADERS = $(shell ls *.h)
SOURCES = $(shell ls *.cpp)

COMPILERFLAGS = -W -Wall
DEBUGFLAGS = -g
CPPCOMPILER = g++

LFLAGS =
LIBS =

INCLUDES = -I.
#INCLUDES += /usr/include/c++/4.2

OBJS = $(SOURCES:.cpp=.o)

BINARY = server

all: $(BINARY)

$(BINARY):  $(OBJS) 
	$(CPPCOMPILER) $(SOURCES) $(COMPILERFLAGS) $(DEBUGFLAGS) $(INCLUDES) -o $(BINARY) $(LFLAGS) $(LIBS)

.PHONY:clean depend

depend:
		makedepend -f- -- $(SOURCES) > .depend_file
clean:
		rm -rf *.o .depend_file $(BINARY) *~

#DO NOT DELETE
