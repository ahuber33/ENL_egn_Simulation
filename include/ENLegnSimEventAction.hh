/// ENLegnSimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLegnSimEventAction_h
#define ENLegnSimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;


//This struct carries statistics for the whole Run
struct RunTally {
  float  IncidentE;
  float  Deposit;
  std::vector<float> EBremCreation;
  std::vector<float> EBremPlaque;
  std::vector<float> ENeutronCreation;
  std::vector<float> ENeutronPlaque;

  inline int operator ==(const RunTally& right) const
  {return (this==&right);}
};



class ENLegnSimEventAction : public G4UserEventAction
{
public:
  ENLegnSimEventAction(char*);
  ~ENLegnSimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddEdep(G4float edep){Statistics.Deposit+=edep;}
  void SetIncidentE(G4float e){Statistics.IncidentE =e;}
  G4float GetIncidentE(){return Statistics.IncidentE;}
  void FillEBremCreation(G4float e){Statistics.EBremCreation.push_back(e);}
  void FillEBremPlaque(G4float e){Statistics.EBremPlaque.push_back(e);}
  void FillENeutronCreation(G4float e){Statistics.ENeutronCreation.push_back(e);}
  void FillENeutronPlaque(G4float e){Statistics.ENeutronPlaque.push_back(e);}

private:

  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;

  G4String suffixe;





};


#endif
