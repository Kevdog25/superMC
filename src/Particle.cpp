#include <cmath>
#include <fstream>
#include <istream>
#include <iomanip>

#include "Particle.h"
#include "GaussianDistribution.h"
using namespace std;

Particle::Particle(double x0, double y0, double z0,GaussianDistribution* dist)
{
   x = x0; 
   y = y0; 
   z = z0;
   gaussDist = dist;
   numberOfCollision = 0;
}

// Initialize the particle from a 
Particle::Particle(Particle* inPart)
{
    x = inPart->getX();
    y = inPart->getY();
    z = inPart->getZ();
    gaussDist = inPart.getGaussDist();
    numberOfCollision = 0;
}

Particle::~Particle()
{
}

double Particle::getInternalStructDensity(double xg, double yg, double quarkWidth, GaussianDistribution *gaussDist)
{
   double dens = 0;

   if(!QuarkGen)
     getQuarkPos(ValenceQuarks,gaussDist);
   
   double d;
   for(int i(0);i<3;i++)
   {
   	d = pow(ValenceQuarks[i][0]+x-xg,2)+pow(ValenceQuarks[i][1]+y-yg,2); //The squared distance between the Quark and the grid
   	dens += flucfactors[i]*(1./(2*M_PI*quarkWidth*quarkWidth))*exp(-d/(2*quarkWidth*quarkWidth))/3; //Divide a total of 1 density between 3 quarks
   }
   return dens;
}

void Particle::generateQuarkPosition()
{
   double x, y;

  
   for(int i = 0; i < 3; i++)
   {
     x = gaussDist->rand();
     y = gaussDist->rand();

     ValenceQuarks[i][0] = x;
     ValenceQuarks[i][1] = y;
   }
}
