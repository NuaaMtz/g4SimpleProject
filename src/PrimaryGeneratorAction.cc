#include "PrimaryGeneratorAction.hh"
#include <G4RunManager.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  // Create a particle gun
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  // Set the particle type
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);

  // GPS
  // fParticleGPS=new G4GeneralParticleSource();
}
PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  delete fParticleGun;
  // GPS
  //  delete fParticleGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
  // Generate the primary vertex
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0., -0.25 * m));
  // set angle
  G4double phi = (-12.0 + 24.0 * G4UniformRand()) * deg;
  G4double theta = (-25.0 + 50.0 * G4UniformRand()) * deg;
  G4double v1 = std::sin(theta) * std::cos(phi);
  G4double v2 = std::sin(theta) * std::sin(phi);
  G4double v3 = std::cos(theta);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(v1, v2, v3));
  // energy
  G4double energy = 4 * MeV + (7.5 * MeV - 4 * MeV) * G4UniformRand();
  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->GeneratePrimaryVertex(anEvent);

  // GPS
  // fParticleGPS->GeneratePrimaryVertex(anEvent);
}