/// ENLegnSimMaterials.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

// This class is used to create a plastic scintillator.

#ifndef ENLegnSimMaterials_h
#define ENLegnSimMaterials_h


#include "G4MaterialPropertiesTable.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class G4Material;

class ENLegnSimMaterials
{
public:

  ENLegnSimMaterials(G4String prop_buildfile);
  ~ENLegnSimMaterials();
  void Construct();

public:
  G4Material *GetMaterial(G4String);


private:

  static const G4String path;

  G4Element* elementH;
  G4Element* elementC;
  G4Element* elementO;
  G4Element* elementF;
  G4Element* elementTi;
  G4Element* elementSi;
  G4Element* elementB;
  G4Element* elementNa;
  G4Element* elementAl;
  G4Element* elementN;
  G4Element* elementFe;
  G4Element* elementNi;
  G4Element* elementCr;
  G4Element* elementMn;
  G4Element* elementCu;
  G4Element* elementSn;
  G4Element* elementSb;
  G4Element* elementMg;
  G4Element* elementZn;
  G4Element* elementCl;
  G4Element* elementK;
  G4Element* elementPb;
  G4Element* elementLa;
  G4Element* elementBr;
  G4Element* elementW;

  G4Isotope* Fe56;

  G4Material *SiO2;
  G4Material *B2O3;
  G4Material *Na2O;
  G4Material *Al2O3;
  G4Material *Air;
  G4Material *Fer;
  G4Material *Inox;
  G4Material *Cuivre;
  G4Material *Carbon;
  G4Material *Kapton;
  G4Material *Acier;
  G4Material *N2;
  G4Material *H2O;
  G4Material *Polypropylene;
  G4Material *Compensation;
  G4Material *Papier;
  G4Material *Nylon;
  G4Material *teflon;
  G4Material *mousse;
  G4Material *Neoprene;
  G4Material *Mica;
  G4Material *Plomb_Antimoine;
  G4Material *Plomb;
  G4Material *LaBr3;
  G4Material *bs_glass;
  G4Material *polysty;
  G4Material *Ti02;
  G4Material *coating;
  G4Material *scintillator;
  G4Material *Vacuum;
  G4Material *VacuumWorld;
  G4Material *plastic;
  G4Material *mylar;
  G4Material *grease;
  G4Material *cargille;
  G4Material *PMMA;
  G4Material *Alu;
  G4Material* Tungstene;

  G4double scintAbsorbconst;
  G4double scintIndexconst;
  G4double scalingfactor_low;
  G4double scalingfactor_high;
  G4double pop_scalingfactor_low;
  G4double pop_scalingfactor_high;
  G4double lightyield;
  G4double paint_ref_coeff;
  G4double mylar_ref_coeff;
  G4double pWavelength;
  G4double ratio;


};
#endif
