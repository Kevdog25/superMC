#ifndef PARTICLE_h
#define PARTICLE_h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "GaussianDistribution.h"

class Particle
{
 protected:
  double x,y,z;
  int numberOfCollision;
  
  // added by Kevin Welsh
  double quarkWidth;
  double energy;
  GaussianDistribution* gaussDist;

 public:
  double ValenceQuarks[3][3];
  
  Particle(double x0,double y0, double z0,GaussianDistribution* dist);
  Particle(Particle* inPart);
  ~Particle();

  double getX() {return x;}
  double getY() {return y;}
  double getZ() {return z;}
  double getEnergy() {return energy;}
  GaussianDistribution* getGaussDist(){return gaussDist;}
  void   setX(double a) {x=a;}
  void   setY(double a) {y=a;}
  void   setZ(double a) {z=a;}
  void   setEnegerg(double a) {energy=a;}
  void   setGaussDist(GaussianDistribution* dist){gaussDist = dist;}
  

  int    getNumberOfCollision() {return numberOfCollision;}
  void   setNumberOfCollision() {numberOfCollision++;}
  void   setNumberOfCollision(int i) {numberOfCollision=i;}

  // functions for nucleon substructure added by Kevin Welsh
  void generateQuarkPosition();
};

#endif
