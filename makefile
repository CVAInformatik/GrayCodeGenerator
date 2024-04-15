
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O3

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm *.o


GrayCodeGenerator.o  : GrayCodeGenerator.cpp  GrayCodeGenerator.h

GrayCodeGenerator : GrayCodeGenerator.o



