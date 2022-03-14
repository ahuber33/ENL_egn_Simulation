/// ENLegnSimPhysics.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLegnSimPhysics.hh"
//#include "G4MuNuclearInteraction.hh"
#include "G4KokoulinMuonNuclearXS.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ios.hh"
#include "G4OpWLS.hh"
#include "G4GenericIon.hh"
#include "G4Decay.hh"
#include "G4IonConstructor.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
//#include "NeutronHPphysics.hh"
// Processes

#include "G4HadronElasticProcess.hh"
#include "G4ParticleHPElasticData.hh"
#include "G4ParticleHPThermalScatteringData.hh"
#include "G4ParticleHPElastic.hh"
#include "G4ParticleHPThermalScattering.hh"

#include "G4HadronInelasticProcess.hh"
#include "G4ParticleHPInelasticData.hh"
#include "G4ParticleHPInelastic.hh"

#include "G4NeutronCaptureProcess.hh"
#include "G4ParticleHPCaptureData.hh"
#include "G4ParticleHPCapture.hh"

#include "G4NeutronFissionProcess.hh"
#include "G4ParticleHPFissionData.hh"
#include "G4ParticleHPFission.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4LENDorBERTModel.hh"
#include "G4LENDCombinedCrossSection.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "G4LowEGammaNuclearModel.hh"
#include "G4CascadeInterface.hh"

using namespace CLHEP;

// Taken from N06 and LXe examples in GEANT4

ENLegnSimPhysics::ENLegnSimPhysics():  G4VModularPhysicsList(), fThermal(true)
{
  // Here used the default cut value you have typed in

  //defaultCutValue = 0.001*mm; //0.001
  defaultCutValue = 1*mm; //0.001
  //was 0.5*mm

  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option3();
}

ENLegnSimPhysics::~ENLegnSimPhysics(){
  delete raddecayList;
  delete emPhysicsList;
}

void ENLegnSimPhysics::ConstructParticle()
{
  // Here are constructed all particles you have chosen
  particleList->ConstructParticle();
  //ConstructBosons();
  //ConstructLeptons();
  //ConstructMesons();
  //ConstructBaryons();
  //ConstructAllShortLiveds();
  //G4GenericIon::GenericIonDefinition();
  //G4IonConstructor iConstructor;
  //iConstructor.ConstructParticle();
}



void ENLegnSimPhysics::ConstructProcess()
{
  // Transportation, electromagnetic and general processes

  AddTransportation();
  //ConstructEM();
  //ConstructGeneral();
  // Electromagnetic physics list
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();
  ConstructNeutron();

  G4HadronInelasticProcess* process
  = new G4HadronInelasticProcess("photonNuclear", G4Gamma::Definition());
  process->AddDataSet( new G4PhotoNuclearCrossSection );

  // to not register a model, set Emax=0; eg. Emax1 = 0.
  const G4double Emax1 = 200*MeV, Emax2 = 10*GeV;

  if (Emax1 > 0.) {  // model 1
    G4LowEGammaNuclearModel* model1 = new G4LowEGammaNuclearModel();
    model1->SetMaxEnergy(Emax1);
    process->RegisterMe(model1);
  }

  if (Emax2 > 0.) {  // model 2
    G4CascadeInterface* model2 = new G4CascadeInterface();
    G4double Emin2 = std::max(Emax1-1*MeV, 0.);
    model2->SetMinEnergy(Emin2);
    model2->SetMaxEnergy(Emax2);
    process->RegisterMe(model2);
  }

  G4ProcessManager* pManager = G4Gamma::Gamma()->GetProcessManager();
  pManager->AddDiscreteProcess(process);
}

void ENLegnSimPhysics::ConstructNeutron()
{
  G4ParticleDefinition* neutron = G4Neutron::Neutron();
  G4ProcessManager* pManager = neutron->GetProcessManager();

  // delete all neutron processes if already registered
  //
  G4VProcess* process = 0;
  process = pManager->GetProcess("hadElastic");
  if (process) pManager->RemoveProcess(process);
  //
  process = pManager->GetProcess("neutronInelastic");
  if (process) pManager->RemoveProcess(process);
  //
  process = pManager->GetProcess("nCapture");
  if (process) pManager->RemoveProcess(process);
  //
  process = pManager->GetProcess("nFission");
  if (process) pManager->RemoveProcess(process);

  // (re) create process: elastic
  //
  G4HadronElasticProcess* process1 = new G4HadronElasticProcess();
  pManager->AddDiscreteProcess(process1);
  //
  // model1a
  G4ParticleHPElastic*  model1a = new G4ParticleHPElastic();
  process1->RegisterMe(model1a);
  process1->AddDataSet(new G4ParticleHPElasticData());
  //
  // model1b
  if (fThermal) {
    model1a->SetMinEnergy(4*eV);
    G4ParticleHPThermalScattering* model1b = new G4ParticleHPThermalScattering();
    process1->RegisterMe(model1b);
    process1->AddDataSet(new G4ParticleHPThermalScatteringData());
  }

  // (re) create process: inelastic
  //
  G4HadronInelasticProcess* process2 =
  new G4HadronInelasticProcess( "neutronInelastic", G4Neutron::Definition() );
  pManager->AddDiscreteProcess(process2);
  //
  // cross section data set
  G4ParticleHPInelasticData* dataSet2 = new G4ParticleHPInelasticData();
  process2->AddDataSet(dataSet2);
  //
  // models
  G4ParticleHPInelastic* model2 = new G4ParticleHPInelastic();
  process2->RegisterMe(model2);

  // (re) create process: nCapture
  //
  G4NeutronCaptureProcess* process3 = new G4NeutronCaptureProcess();
  pManager->AddDiscreteProcess(process3);
  //
  // cross section data set
  G4ParticleHPCaptureData* dataSet3 = new G4ParticleHPCaptureData();
  process3->AddDataSet(dataSet3);
  //
  // models
  G4ParticleHPCapture* model3 = new G4ParticleHPCapture();
  process3->RegisterMe(model3);

  // (re) create process: nFission
  //
  G4NeutronFissionProcess* process4 = new G4NeutronFissionProcess();
  pManager->AddDiscreteProcess(process4);
  //
  // cross section data set
  G4ParticleHPFissionData* dataSet4 = new G4ParticleHPFissionData();
  process4->AddDataSet(dataSet4);
  //
  // models
  G4ParticleHPFission* model4 = new G4ParticleHPFission();
  process4->RegisterMe(model4);
}

void ENLegnSimPhysics::SetCuts()
{
  // defaultCutValue you have typed in is used

  if (verboseLevel >1){
    G4cout << "opticalPhysics::SetCuts:";
  }
  SetCutsWithDefault();
  //  SetCutValue(5*mm,"opticalphoton");
}
