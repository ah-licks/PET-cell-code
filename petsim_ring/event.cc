#include "event.hh"

extern G4int validCases;

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
    fTime.clear();
    fPosition.clear();
}

MyEventAction::~MyEventAction()
{}

G4double angleDifference(G4ThreeVector vectorA, G4ThreeVector vectorB) {
    if (vectorA.mag() == 0 || vectorB.mag() == 0) return -1;
    //due to rounding errors probably numbers slightly larger than 1 will be set to 1
    G4double cosAngle = (vectorA.getX() * vectorB.getX() + vectorA.getY() * vectorB.getY() + vectorA.getZ() * vectorB.getZ()) / (vectorA.mag() * vectorB.mag());
    if (cosAngle > 1.0) cosAngle = 1.0;
    if (cosAngle < -1.0) cosAngle = -1.0;
    return acos(cosAngle) * 180.0 / M_PI;
}

G4bool wantedTrajectory(std::vector<std::pair<G4ThreeVector, G4double>> positions) {
    G4double acceptedAngleDifference = 25.0;

    if (positions.size() == 0) return false;
    if (positions.size() == 1) return true;
    if (angleDifference(positions[0].first, positions[1].first - positions[0].first) > acceptedAngleDifference) return false;
    for (G4int i = 1; i < positions.size() - 1; i++) {
        if (angleDifference(positions[i].first - positions[i - 1].first, positions[i + 1].first - positions[i].first) > acceptedAngleDifference) return false;
    }
    if (angleDifference(positions[0].first, positions[positions.size() - 1].first) > acceptedAngleDifference) return false;
    
    return true;
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
    fTime.clear();
    fPosition.clear();
}

void MyEventAction::EndOfEventAction(const G4Event* anEvent)
{
    //checking which positions and times belong to which particle
    std::vector<std::pair<G4ThreeVector, G4double>> particleOne;
    std::vector<std::pair<G4ThreeVector, G4double>> particleTwo;
    particleOne.push_back({fPosition[0], fTime[0]});
    G4bool switchParticle = false;
    for (G4int i = 1; i < fPosition.size(); i++) {
    	if (std::signbit(fPosition[i].getX()) != std::signbit(particleOne[0].first.getX())) {
    	    switchParticle = true;
    	}
    	if (switchParticle) {
    	    particleTwo.push_back({fPosition[i], fTime[i]});
    	} else {
    	    particleOne.push_back({fPosition[i], fTime[i]});
    	}
    }
    
    /*
    //sorting
    std::sort(particleOne.begin(), particleOne.end(), [](auto &left, auto &right) {
    	return left.second < right.second;
    });
    std::sort(particleTwo.begin(), particleTwo.end(), [](auto &left, auto &right) {
    	return left.second < right.second;
    });
    */
    
    //saving data
    if (fEdep >= 1.0 && wantedTrajectory(particleOne) && wantedTrajectory(particleTwo)) {
    	validCases++;
        G4AnalysisManager *man = G4AnalysisManager::Instance();
        man->FillNtupleDColumn(0, fEdep);
        man->FillNtupleDColumn(1, particleOne[0].first.getX());
        man->FillNtupleDColumn(2, particleOne[0].first.getY());
        man->FillNtupleDColumn(3, particleOne[0].first.getZ());
        man->FillNtupleDColumn(4, particleTwo[0].first.getX());
        man->FillNtupleDColumn(5, particleTwo[0].first.getY());
        man->FillNtupleDColumn(6, particleTwo[0].first.getZ());
        man->FillNtupleDColumn(7, particleOne[0].second - particleTwo[0].second);
        man->FillNtupleDColumn(8, anEvent->GetPrimaryVertex(0)->GetX0()); //starting x
        man->FillNtupleDColumn(9, anEvent->GetPrimaryVertex(0)->GetY0()); //starting y
        man->FillNtupleDColumn(10, anEvent->GetPrimaryVertex(0)->GetZ0()); //starting z
        man->AddNtupleRow(0);
    }
}
