/// ENLegnSimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLegnSimVisManager_h
#define ENLegnSimVisManager_h 1

#include "G4VisManager.hh"


class ENLegnSimVisManager: public G4VisManager {

public:

  ENLegnSimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
