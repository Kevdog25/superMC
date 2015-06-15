#ifndef Participant_h
#define Participant_h

#include <vector>
#include "Particle.h"
#include "arsenal.h"
#include <cmath>

class Participant
{
protected:
    int nucl;
    Particle* part;
    double xsave,ysave;
    double fluctfactor;

    //EntropyFluctuations (Kevin)
    static double ImprintArrayRHIC[][600];
    static double ImprintArrayLHC[][600];
    int FluctuationSamplePosition[2];
    double binWidth;
public:
    std::vector<int> who_hit_me; // those nucleons collided with this nucleon, their indices in the binaryCollision array is stored here. This is not against the capsulate rule since the interpretation of these vector replied on external programs, and this vector is just a storage space for additional info.
    Participant(Particle* part0,int i) {
      part=part0;
      nucl=i;
      xsave = part->getX();
      ysave = part->getY();
      FluctuationSamplePosition[0] = 0;
      FluctuationSamplePosition[1] = 0;
      binWidth = 0.1;
    }
    ~Participant() {};

    Particle* getParticle() {return part;}
    int getNumberOfCollision() {return part->getNumberOfCollision();}
    double getX() {return part->getX();}
    double getY() {return part->getY();}
    double getXorg() {return xsave;}
    double getYorg() {return ysave;}
    void setX(double a) {part->setX(a);}
    void setY(double a) {part->setY(a);}
    int    isNucl() {return nucl;}
    void   setNucl(int i) {nucl=i;}
    void resetCoordinate() {part->setX(xsave);part->setY(ysave);}

    void setfluctfactor(double fluct) {fluctfactor = fluct;}
    double getfluctfactor() {return fluctfactor;}
    
    //(Kevin)
    double getGluonFluc(double xgrid,double ygrid,double r,double ecm){
        if(FluctuationSamplePosition[0]==0){
            int arraySize = 600;
            double margin = r/binWidth;

            FluctuationSamplePosition[0] = ((arraySize-margin-1)-(margin+1))*drand48()+(margin)+1;
            FluctuationSamplePosition[1] = ((arraySize-margin-1)-(margin+1))*drand48()+(margin)+1;
        }
        int flucSample[2];
        int gridDiff[2];

        gridDiff[0] = int((xgrid - part->getX())/binWidth);
        gridDiff[1] = int((ygrid - part->getY())/binWidth);

        flucSample[0] = gridDiff[0]+FluctuationSamplePosition[0];
        flucSample[1] = gridDiff[1]+FluctuationSamplePosition[1];
        if(abs(ecm - 5020) < abs(ecm-200))
            return ImprintArrayLHC[flucSample[0]][flucSample[1]];
        else 
            return ImprintArrayRHIC[flucSample[0]][flucSample[1]];
        }
};

#endif
