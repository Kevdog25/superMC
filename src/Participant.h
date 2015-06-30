#ifndef Participant_h
#define Participant_h

#include <vector>
#include "Particle.h"
#include "arsenal.h"
#include <cmath>

class Participant: public Particle
{
protected:
    int nucl;
    double xsave,ysave;
    
    //EntropyFluctuations (Kevin)
    static double ImprintArrayRHIC[][600];
    static double ImprintArrayLHC[][600];
    int FluctuationSamplePosition[2];
    double binWidth;
public:
    std::vector<int> who_hit_me; // those nucleons collided with this nucleon, their indices in the binaryCollision array is stored here. This is not against the capsulate rule since the interpretation of these vector replied on external programs, and this vector is just a storage space for additional info.
    Participant(Particle* part0,int i) : Particle(part0) {
      nucl=i;
      
      xsave = x;
      ysave = y;
      
      FluctuationSamplePosition[0] = 0;
      FluctuationSamplePosition[1] = 0;
      binWidth = 0.1;
    }
    ~Participant() {};

    double getXorg() {return xsave;}
    double getYorg() {return ysave;}
    int    getNucl() {return nucl;}
    void   setNucl(int i) {nucl=i;}
    void resetCoordinate() {x = xsave; y = ysave;}

    //(Kevin)
    double getSmoothDensity(double xg, double yg);
    double getFluctuatedDensity(double xg, double yg);
    double getFluctuatedDensity(double xg, double yg)
    {
       double dens = 0;


       double d;
       for(int i(0);i<3;i++)
       {
            d = pow(ValenceQuarks[i][0]+x-xg,2)+pow(ValenceQuarks[i][1]+y-yg,2); //The squared distance between the Quark and the grid
            dens += flucfactors[i]*(1./(2*M_PI*quarkWidth*quarkWidth))*exp(-d/(2*quarkWidth*quarkWidth))/3; //Divide a total of 1 density between 3 quarks
       }
       return dens;
    }
    double getGluonFluc(double xgrid,double ygrid,double r,double ecm){
        if(FluctuationSamplePosition[0]==0){
            int arraySize = 600;
            double margin = r/binWidth;

            FluctuationSamplePosition[0] = ((arraySize-margin-1)-(margin+1))*drand48()+(margin)+1;
            FluctuationSamplePosition[1] = ((arraySize-margin-1)-(margin+1))*drand48()+(margin)+1;
        }
        int flucSample[2];
        int gridDiff[2];

        gridDiff[0] = int((xgrid - x)/binWidth);
        gridDiff[1] = int((ygrid - y)/binWidth);

        flucSample[0] = gridDiff[0]+FluctuationSamplePosition[0];
        flucSample[1] = gridDiff[1]+FluctuationSamplePosition[1];
        if(abs(ecm - 5020) < abs(ecm-200))
            return ImprintArrayLHC[flucSample[0]][flucSample[1]];
        else 
            return ImprintArrayRHIC[flucSample[0]][flucSample[1]];
        }
};

#endif
