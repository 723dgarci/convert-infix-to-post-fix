CFLAGS = -std=c++11 -Wall -pedantic 

all: in2post.x 

in2post.x: in2post.o 
	g++ $(CFLAGS) -o $@ $^

in2post.o: stack.h in2post.cpp
	g++ $(CFLAGS) -c $^

clean:
	rm *.o *.gch
