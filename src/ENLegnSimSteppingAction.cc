/// ENLegnSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLegnSimSteppingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "ENLegnSimRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "ENLegnSimEventAction.hh"
#include <iostream>
#include <fstream>
#include "G4Material.hh"
#include "G4Trajectory.hh"
#include "ENLegnSimGeometry.hh"
#include "G4StepPoint.hh"
#include "TRandom3.h"
#include "TF1.h"


using namespace CLHEP;

const G4String ENLegnSimSteppingAction::path = "../simulation_input_files/";

ENLegnSimSteppingAction::ENLegnSimSteppingAction()
{}

  ENLegnSimSteppingAction::~ENLegnSimSteppingAction(){}
  void ENLegnSimSteppingAction::UserSteppingAction(const G4Step *aStep){


    //###################################
    // Déclaration of functions/variables
    //###################################
    G4Track* theTrack = aStep->GetTrack();
    G4String partname = aStep->GetTrack()->GetDefinition()->GetParticleName();
    ENLegnSimRunAction *runac = (ENLegnSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    G4EventManager *evtman = G4EventManager::GetEventManager();
    ENLegnSimEventAction *evtac = (ENLegnSimEventAction*)evtman->GetUserEventAction();
    G4String endproc = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4int Parent_ID = aStep->GetTrack()->GetParentID();
    G4int StepNo = aStep->GetTrack()->GetCurrentStepNumber();

    G4double Ecin = aStep->GetPreStepPoint()->GetKineticEnergy()/keV;
    G4double x = aStep->GetTrack()->GetPosition().x();
    G4double y = aStep->GetTrack()->GetPosition().y();
    G4double z = aStep->GetTrack()->GetPosition().z();
    G4double r = sqrt(x*x + y*y);
    G4double my_dist_after = theTrack->GetTrackLength()/mm;





    //#######################################################################
    //#######################################################################
    //###########################START EM INFOS PART#########################
    //#######################################################################
    //#######################################################################


    //###################################################################################
    //###################################################################################
    //######################### CODE FOR EMMANUEL THESIS PLOT  ##########################
    //###################################################################################
    //###################################################################################

//     if(Parent_ID>0 &&theTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay")
//     {
//       if (partname == "gamma")
//       {
//         if (StepNo ==1)
//         {
//           evtac->FillEGammaCreation(Ecin);
//           //G4cout << "E gamma = " << Ecin << G4endl;
//         }
//       }
//
//       if(partname == "e-")
//         if (StepNo ==1)
//         {
//           evtac->FillEElecCreation(Ecin);
//           //G4cout << "E e- = " << Ecin << G4endl;
//         }
//     }
//
// if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "CdTe")
// {
//   evtac->AddEdep(aStep->GetTotalEnergyDeposit()/keV);
//   evtac->FillEElecDeposit(aStep->GetTotalEnergyDeposit()/keV);
//   evtac->FillPositionDeposit(z+1);
//   //G4cout << "Edep = " << aStep->GetTotalEnergyDeposit()/keV << " at z = " << z << G4endl;
// }
//
// if(Parent_ID==0 && StepNo==1)
// {
//   evtac->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
// }
//



  //###################################################################################
  //###################################################################################
  //############### CODE FOR VALERIA/VEGA ANALYSIS WITH NEUTRONS ######################
  //###################################################################################
  //###################################################################################

    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "PlaqueAcier") {evtac->AddEdep(aStep->GetTotalEnergyDeposit()/keV);}

    if(Parent_ID==0 && StepNo==1)
    {
      evtac->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
    }

    if(Parent_ID >0 && partname == "gamma")
    {
      if(aStep->GetTrack()->GetCreatorProcess()->GetProcessName()=="eBrem")
      {
        if(StepNo==1)
        {
          evtac->FillEBremCreation(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
          //G4cout << "E gamma brem = " << aStep->GetPreStepPoint()->GetKineticEnergy()/keV << G4endl;
        }
        if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "PhysicalWorld")
        {
          evtac->FillEBremPlaque(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
          //G4cout << "E gamma brem en sortie plaque = " << aStep->GetPreStepPoint()->GetKineticEnergy()/keV << G4endl;
        }
      }
    }

    if(Parent_ID >0 && partname =="neutron")
    {
      if(aStep->GetTrack()->GetCreatorProcess()->GetProcessName()=="photonNuclear")
      {
        if(StepNo ==1)
        {
          //G4cout << "neutron process : " << aStep->GetTrack()->GetCreatorProcess()->GetProcessName() << G4endl;
          //G4cout << "neutron energy creation = " << aStep->GetPreStepPoint()->GetKineticEnergy()/keV << G4endl;
          evtac->FillENeutronCreation(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
        }

        if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "PhysicalWorld")
        {
          evtac->FillENeutronPlaque(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
          //G4cout << "neutron energy en sortie plaque = " << aStep->GetPreStepPoint()->GetKineticEnergy()/keV << G4endl;
        }

      }
    }

    //
    // if(partname =="gamma" && endproc !="Transportation")
    // {
    //   //G4cout << "Interaction :" << endproc << G4endl;
    // }
    //
    // if(endproc =="Rayl") evtac->SetInteraction(1);
    // if(endproc =="compt") evtac->SetInteraction(2);
    // if(endproc =="phot") evtac->SetInteraction(3);
    // if(endproc =="conv") evtac->SetInteraction(4);


    // if(Parent_ID>0)// && aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "PhysicalWorld")
    //   {
    //     //G4cout << "Ici" << G4endl
    //     theTrack->SetTrackStatus(fStopAndKill);
    //   }






  }
