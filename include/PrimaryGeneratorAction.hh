/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 14:43:45
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:00:13
 * @FilePath: /betatron/include/PrimaryGeneratorAction.hh
 * @Description: primary generator action，not only particle gun but also GPS. But they could not be used at the same time
 */
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();
  virtual void GeneratePrimaries(G4Event *);

 

//* particle gun
public:
    G4ParticleGun *GetParticleGun() const { return fParticleGun; }
private:
    G4ParticleGun *fParticleGun; // G4 particle gun


// GPS
/*!  GPS
public:
    G4GeneralParticleSource *GetGPS() const { return fParticleGPS; }
private:
    G4GeneralParticleSource *fParticleGPS; // G4 particle GPS
*/  
};

#endif