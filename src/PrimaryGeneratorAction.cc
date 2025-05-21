/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 14:44:07
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 22:25:45
 * @FilePath: /betatron/src/PrimaryGeneratorAction.cc
 * @Description: primary generator action，not only particle gun but also GPS. But they could not be used at the same time
 */
#include "PrimaryGeneratorAction.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4RunManager.hh>
#include <G4ThreeVector.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  // Create a particle gun

  // GPS
  // fParticleGPS=new G4GeneralParticleSource();
}
PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  delete fParticleGun;
  // GPS
  //  delete fParticleGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
  auto man = G4Root::G4AnalysisManager::Instance();

  // particle gun counts
  G4int n_particles = 3;
  fParticleGun = new G4ParticleGun(n_particles);

  // Set the particle type
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);

  for (G4int i = 0; i < n_particles; ++i) {
    // direction
    // \theta 
    G4ThreeVector dir = ConeDirection();
    fParticleGun->SetParticleMomentumDirection(dir);

    // Energy
    G4double energy = 4 * MeV + (7.5 * MeV - 4 * MeV) * G4UniformRand();
    fParticleGun->SetParticleEnergy(energy);

    // position
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0., -0.25 * m));

    // Fill to Roor files
    man->FillNtupleDColumn(2, 0, energy * dir.x());
    man->FillNtupleDColumn(2, 1, energy * dir.y());
    man->FillNtupleDColumn(2, 2, energy * dir.z());
    man->AddNtupleRow(2);

    // Generate the primary vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
}

G4ThreeVector PrimaryGeneratorAction::IsotropicSource() {
  // 各向同性源
  G4double cosTheta = 2 * G4UniformRand() - 1;
  G4double phi = 2. * 3.14159265 * G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta * cosTheta);
  G4double ux = sinTheta * std::cos(phi);
  G4double uy = sinTheta * std::sin(phi);
  G4double uz = cosTheta;
  return G4ThreeVector(ux, uy, uz);
}

G4ThreeVector PrimaryGeneratorAction::ConeDirection() {
  G4double theta_max = 30.0 * CLHEP::deg;
  // theta_max 单位为弧度，方向锥体朝z轴正方向
  G4double cosThetaMin = std::cos(0.0);
  G4double cosThetaMax = std::cos(theta_max);
  G4double cosTheta = cosThetaMin + (cosThetaMax - cosThetaMin) * G4UniformRand();
  G4double theta = std::acos(cosTheta);
  G4double phi = 2. * CLHEP::pi * G4UniformRand();

  G4double ux = std::sin(theta) * std::cos(phi);
  G4double uy = std::sin(theta) * std::sin(phi);
  G4double uz = std::cos(theta);

  return G4ThreeVector(ux, uy, uz);
}