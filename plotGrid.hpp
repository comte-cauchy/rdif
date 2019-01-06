#ifndef SDLINTERFACE_HPP__
#define SDLINTERFACE_HPP__

#include <vector>
#include <SDL.h>
using namespace std;


class SDLInterface
{
public:
	SDLInterface(unsigned nx, unsigned ny, unsigned nz=1, unsigned z=0);
	~SDLInterface();
	void plotGrid(double* u, double* v);
	bool quit();
private:
	const unsigned SCREEN_WIDTH;
	const unsigned SCREEN_HEIGHT;
	SDL_Window* window;
	SDL_Surface* screen;
	SDL_Surface* gridSurface;
	char* pixels;
	unsigned nx,ny,nz,z;
 	SDL_Event e;
};

#endif //SDLINTERFACE_HPP__
