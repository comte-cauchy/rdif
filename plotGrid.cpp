#include <iostream>
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "plotGrid.hpp"
#include <vector>
using namespace std;

SDLInterface::SDLInterface(unsigned nx, unsigned ny, unsigned nz, unsigned z):nx(nx),ny(ny),nz(nz),z(z),SCREEN_WIDTH(nx),SCREEN_HEIGHT(ny)
{
	SDL_Init( SDL_INIT_VIDEO ); 
	window = SDL_CreateWindow( "Reaction Diffusion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	screen = SDL_GetWindowSurface( window );
	pixels = new char[(unsigned long)nx * (unsigned long)ny *3];
}


SDLInterface::~SDLInterface()
{
	//Deallocate surface
	SDL_FreeSurface( gridSurface );
	gridSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	delete[] pixels;
	//Quit SDL subsystems
	SDL_Quit();
}
bool SDLInterface::quit()
{
	while( SDL_PollEvent( &e ) != 0 ) {
		//User requests quit
		if( e.type == SDL_QUIT )
		return true;
	}
}
void SDLInterface::plotGrid( vector<double> u, vector<double> v)
{


	for (unsigned y = 0;y<ny;y++)
	{
		for (unsigned x = 0;x<nx;x++)
		{
			unsigned long i = x+nx*y;
			pixels[3*i] = u[i+nx*ny*z]*255;
			pixels[3*i+1] = v[i+nx*ny*z]*255;
			pixels[3*i+2] = 0;
		}
	}
	
	gridSurface = SDL_CreateRGBSurfaceFrom((void*)pixels,
		nx,
		ny,
		3 * 8,          // bits per pixel = 24
		nx * 3,  // pitch
		0x0000FF,              // red mask
		0x00FF00,              // green mask
		0xFF0000,              // blue mask
		0);
	
	//Apply the image
	SDL_BlitSurface( gridSurface, NULL, screen, NULL );
	
	//Update the surface
	SDL_UpdateWindowSurface( window );
}

//int main()
//{
//	SDLInterface plotter(480,480);
//	vector<double> u(480*480,128);
//	vector<double> v(480*480,128);
//	for (unsigned x = 0;x<480;x++)
//	{
//		for (unsigned y = 0;y<480;y++)
//		{
//			unsigned i = x+480*y;
//			u[i] = x/480.;
//			v[i] = y/480.;
//		}
//	}
//	while (true)
//		plotter.plotGrid(u,v);
//	int a;
//	cin >> a;
//	return 0;
//}
