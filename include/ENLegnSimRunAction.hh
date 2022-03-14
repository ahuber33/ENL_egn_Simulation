/// ENLegnSimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLegnSimRunAction_h
#define ENLegnSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "ENLegnSimEventAction.hh"
#include <TFile.h>
#include <vector>

class G4Run;

class ENLegnSimRunAction : public G4UserRunAction
{

public:
  ENLegnSimRunAction(char*);
  ~ENLegnSimRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);
  



private:
  G4String suffixe;
  RunTally Stats;
  TFile *f;
  TTree *theRunTree;
  TBranch *RunBranch;
  time_t start;

};

#endif
