#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4AnalysisManager.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

G4int validCases = 0;

int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
    
	runManager->SetUserInitialization(new MyDetectorConstruction());
    	runManager->SetUserInitialization(new MyPhysicsList());
    	runManager->SetUserInitialization(new MyActionInitialization());
    	
    	runManager->Initialize();
    
	G4UIExecutive *ui = 0;
	if (argc == 1) {
	    ui = new G4UIExecutive(argc, argv);
	}

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	G4int radius = 15; //cm
	G4int cases = 1; //number of data points

	if (ui) {
		//hardcoding because using macro files is hard
    		//UImanager->ApplyCommand("/control/execute vis.mac");
    		for (G4int i = 0; i < cases; i++) {
    		    G4double tmpRadius = G4UniformRand() * radius;
    		    G4double angle = G4UniformRand() * 2 * M_PI;
    		    G4String pos = to_string(tmpRadius * cos(angle)) + " " + to_string(tmpRadius * sin(angle)) + " " + "0";
    		    UImanager->ApplyCommand("/gun/position "+pos+" cm");
    		    while (validCases < 100) UImanager->ApplyCommand("/run/beamOn 1");
    		    validCases = 0;
    		}
		ui->SessionStart();
	} else {
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}

	return 0;
}
