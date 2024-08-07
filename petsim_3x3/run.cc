#include "run.hh"

G4int det1 = 0;
G4int det2 = 0;
G4int det3 = 0;
G4int det4 = 0;
G4int det5 = 0;
G4int det6 = 0;
G4int det7 = 0;
G4int det8 = 0;
G4int det9 = 0;

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    det1 = 0;
    det2 = 0;
    det3 = 0;
    det4 = 0;
    det5 = 0;
    det6 = 0;
    det7 = 0;
    det8 = 0;
    det9 = 0;

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    //man->OpenFile("output"+strRunID.str()+".csv");
    man->OpenFile("output14mm.csv");
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("det1");
    man->CreateNtupleIColumn("det2");
    man->CreateNtupleIColumn("det3");
    man->CreateNtupleIColumn("det4");
    man->CreateNtupleIColumn("det5");
    man->CreateNtupleIColumn("det6");
    man->CreateNtupleIColumn("det7");
    man->CreateNtupleIColumn("det8");
    man->CreateNtupleIColumn("det9");
    man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    //G4cout << det1 << " " << det2 << " " << det3 << " " << det4 << " " << det5 << " " << det6 << " " << det7 << " " << det8 << " " << det9 << "\n";
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->FillNtupleIColumn(0, det1);
    man->FillNtupleIColumn(1, det2);
    man->FillNtupleIColumn(2, det3);
    man->FillNtupleIColumn(3, det4);
    man->FillNtupleIColumn(4, det5);
    man->FillNtupleIColumn(5, det6);
    man->FillNtupleIColumn(6, det7);
    man->FillNtupleIColumn(7, det8);
    man->FillNtupleIColumn(8, det9);
    man->AddNtupleRow();
    
    man->Write();
    //man->CloseFile();
}
