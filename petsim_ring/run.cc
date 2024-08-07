#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    //man->OpenFile("output"+strRunID.str()+".csv");
    man->OpenFile("output.csv");
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleDColumn("energy");
    man->CreateNtupleDColumn("particle1x");
    man->CreateNtupleDColumn("particle1y");
    man->CreateNtupleDColumn("particle1z");
    man->CreateNtupleDColumn("particle2x");
    man->CreateNtupleDColumn("particle2y");
    man->CreateNtupleDColumn("particle2z");
    man->CreateNtupleDColumn("time");
    man->CreateNtupleDColumn("origx");
    man->CreateNtupleDColumn("origy");
    man->CreateNtupleDColumn("origz");
    man->FinishNtuple(0);

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    //man->CloseFile();
}
