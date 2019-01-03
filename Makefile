COMPILER=g++
#FLAGS= -fopenmp -std=c++11 -O0 -ggdb -ftree-vectorizer-verbose=4 -I/usr/include/SDL2/
FLAGS= -std=c++11 -O3 -ftree-vectorizer-verbose=2 -I/usr/include/SDL2/
LFLAGS=-lSDL2 -lSDL2_image -lpthread
EXE=rdif

OBJS=plotGrid.o

all: $(EXE)
$(EXE): $(OBJS) rdif.cpp
	$(COMPILER) $(FLAGS) -o $(EXE) $(OBJS) rdif.cpp $(LFLAGS)
%.o: %.cpp %.hpp
	$(COMPILER) $(FLAGS) -c $<

clean:
	rm -rf *.o *~ $(EXE)


