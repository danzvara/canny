CXX = g++
SOURCEDIR = src
INC = -I/usr/local/include/ -Iinclude/
LDDIR = -L/usr/local/lib/
LDLIBS = -lopencv_core -lopencv_highgui -lopencv_videoio

all: main

main: main.o camera_stream.o
	$(CXX) -o main camera_stream.o main.o $(INC) $(LDDIR) $(LDLIBS)

main.o: $(SOURCEDIR)/main.cpp
	$(CXX) -c $< $(INC) $(LDDIR) $(LDLIBS)

camera_stream.o: $(SOURCEDIR)/camera_stream.cpp
	$(CXX) -c $< $(INC) $(LDDIR) $(LDLIBS)

clean:
	rm *.o main
