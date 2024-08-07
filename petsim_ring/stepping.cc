#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{   
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
    
    if (volume != fScoringVolume) return;
    
    G4double time = step->GetPreStepPoint()->GetGlobalTime();
    G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
    //G4cout << energy << " " << time << " " << position << G4endl;
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);
    if (edep > 0) {
    	fEventAction->GetTime(time);
    	fEventAction->GetPosition(position);
    }
}
