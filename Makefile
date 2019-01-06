COMPILER=g++
#FLAGS= -fopenmp -std=c++11 -O0 -g -I/usr/include/SDL2/
FLAGS= -mavx -fopenmp -g -std=c++11 -O3  -ftree-vectorize -funroll-loops -flto -I/usr/include/SDL2/ -mavx
#FLAGS= -fopenmp -std=c++11 -O1 -funroll-loops -fno-tree-vectorize -I/usr/include/SDL2/
LFLAGS=-lSDL2 -lSDL2_image -lpthread -mavx
EXE=rdif

OBJS=plotGrid.o

all: $(EXE)
$(EXE): $(OBJS) rdif.cpp
	$(COMPILER) $(FLAGS) -o $(EXE) $(OBJS) rdif.cpp $(LFLAGS)
%.o: %.cpp %.hpp
	$(COMPILER) $(FLAGS) -c $<

clean:
	rm -rf *.o *~ $(EXE)


