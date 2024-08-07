#include "generator.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    G4ThreeVector pos(0., 0., 0.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentum(511.*keV);
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
    G4double z0 = 0;
    G4ThreeVector mom(x0, y0, z0);

    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    fParticleGun->SetParticleMomentumDirection(-1*mom);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
