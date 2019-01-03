#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "plotGrid.hpp"
#include <cmath>
using namespace std;

int main(int argc, char* argv[])
{
	//parameters
	const unsigned int nx = 256;
	const unsigned int ny = 256;
	const unsigned int nz = 1;
	const double dimx = 0.2;
	const double dimy = 0.2;
	const double dimz = 0.2;
	const double dt = 0.1;	

	const double ru = 2e-4;
	const double rv = 1e-4;
	const double f = 0.03;
	const double k = 0.06;
	 
	const unsigned int maxiter = (argc>1?atoi(argv[1]):100);
		
	//init
	const unsigned long n = nx*ny*nz;
	const unsigned int dx = 1;
	const unsigned int dy = nx;
	const unsigned long dz = nx*ny;

	const double hinvx = 2*nx/dimx;
	const double hinvy = 2*ny/dimy;
	const double hinvz = 2*nz/dimz;
	
	vector<double> u(n,1.0);
	vector<double> v(n,0.0);
	vector<double> u_old(u);
	vector<double> v_old(v);
	SDLInterface plotter(nx,ny,nz,nz/2);

	for(int x = 118;x<138;x++)
	{
		for(int y = 118;y<138;y++)
		{
			for(int z = 0;z<nz;z++)
			{
				unsigned long i = x + nx*y + nx*ny*z;
				u[i] = 0.5;
				v[i] = 0.25;
			}
		}
	}
	
	//for(int i = 0;i<n;i++)
	//{
	//	double r1 = (double)rand()/RAND_MAX;
	//	double r2 = (double)rand()/RAND_MAX;
	//	double tmp = sqrt(-2*log(r1));
	//	u[i]*=(1+(1+tmp*sin(2*M_PI*r2))*0.01);
	//	v[i]*=(1+(1+tmp*cos(2*M_PI*r2))*0.01);
	//}


	//iterations
	for(unsigned int iter = 0;iter<maxiter && !plotter.quit();iter++)
	{
		if (!(iter%100))
			plotter.plotGrid(u,v);
		
		u.swap(u_old);
		v.swap(v_old);
		
		for(int x = 0;x<nx;x++)
		{	
			for(int y = 0;y<ny;y++)
			{
				for(int z = 0;z<nz;z++)
				{
					unsigned long i = x+nx*y+nx*ny*z;
					double ux = (x+1 < nx?u_old[i+dx]:u_old[i])+(x-1>=0?u_old[i-dx]:u_old[i])-2*u_old[i];
					double uy = (y+1 < ny?u_old[i+dy]:u_old[i])+(y-1>=0?u_old[i-dy]:u_old[i])-2*u_old[i];
					double uz = (z+1 < nz?u_old[i+dz]:u_old[i])+(z-1>=0?u_old[i-dz]:u_old[i])-2*u_old[i];
					double vx = (x+1 < nx?v_old[i+dx]:v_old[i])+(x-1>=0?v_old[i-dx]:v_old[i])-2*v_old[i];
					double vy = (y+1 < ny?v_old[i+dy]:v_old[i])+(y-1>=0?v_old[i-dy]:v_old[i])-2*v_old[i];
					double vz = (z+1 < nz?v_old[i+dz]:v_old[i])+(z-1>=0?v_old[i-dz]:v_old[i])-2*v_old[i];
					u[i] = u_old[i]+dt*ru*(hinvx*ux + hinvy*uy + hinvz*uz);
					v[i] = v_old[i]+dt*rv*(hinvx*vx + hinvy*vy + hinvz*vz);
				}
			}
		}
		for(int i = 0;i<n;i++)
		{	double reaction_quantity = u[i]*v[i]*v[i];
			u[i] += dt*(-reaction_quantity + f*(1-u[i]));
			v[i] += dt*(reaction_quantity - (f+k)*v[i]);
		}
	}
	plotter.plotGrid(u,v);

	
	return 0;
}
