#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "run.hh"
#include "vector"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event* anEvent);
    
    void AddEdep(G4double edep) {fEdep += edep;}
    void GetTime(G4double time) {fTime.push_back(time);}
    void GetPosition(G4ThreeVector position) {fPosition.push_back(position);}
    
private:
    G4double fEdep;
    std::vector<G4double> fTime;
    std::vector<G4ThreeVector> fPosition;
};

#endif
