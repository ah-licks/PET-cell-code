#include "generator.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="opticalphoton";
    G4ParticleDefinition *particle = particleTable->FindParticle("opticalphoton");

    G4ThreeVector pos(0., 0., 0.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentum(7.*eV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4double x0 = G4UniformRand() - 0.5;
    G4double y0 = G4UniformRand() - 0.5;
    G4double z0 = G4UniformRand() - 0.5;
    G4ThreeVector mom(x0, y0, z0);

    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
