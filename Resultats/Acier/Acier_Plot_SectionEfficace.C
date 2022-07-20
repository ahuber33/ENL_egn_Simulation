TGraph* graph(const char* filename, const int nlines, float factor_E, float factor_N)
{

  ifstream file(filename);
  float E[nlines], N[nlines];

  for (int i=0; i<nlines; i++)
    {
      file >> E[i] >> N[i];
      E[i] = E[i]*factor_E;
      N[i] = N[i]*factor_N;
      //      cout << E[i] << " " << N[i] << endl;
    }
  file.close();

  TGraph* graph = new TGraph(nlines, E, N);

  return graph;
}



float section_efficace(const char* filename, float Nsim, int variable)
{
  TFile* file = new TFile(filename);
  vector <float> *a=0;
  TTree *Tree = (TTree*)file->Get("theRunTree");
  Tree->SetBranchAddress("ENeutronCreation", &a);
  float Entries = Tree->GetEntries();
  float n=0;
  float p=0;

  for(int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      if(a->size()>variable){n++;}
    }

  p = n/Nsim;
  float A = 56.; //g/mol
  float Na = 6.022e+23; //mol-1
  float rho = 7.86; //g/cm-3
  float d = 0.01; //cm
  
  float section_efficace = ((A*p)/(Na*rho*d))*1e24;

  cout << "Section efficace [" << filename << "] = " << section_efficace << endl;

  
  return section_efficace;

  delete file;
  delete Tree;
}


float err_section_efficace(const char* filename, float Nsim, int variable)
{
  TFile* file = new TFile(filename);
  vector <float> *a;
  TTree *Tree = (TTree*)file->Get("theRunTree");
  Tree->SetBranchAddress("ENeutronCreation", &a);
  float Entries = Tree->GetEntries();
  float n=0;
  float p=0;
  
  for(int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      if(a->size()>variable){n++;}
    }

  p = sqrt(n)/Nsim;
  float A = 56; //g/mol
  float Na = 6.022e+23; //mol-1
  float rho = 7.86; //g/cm-3
  float d = 0.01; //cm
  
  float section_efficace = ((A*p)/(Na*rho*d))*1e24;

  cout << "Section effiace [" << filename << "] = " << section_efficace << endl;
  //a->clear();
  
  return section_efficace;
}


void Acier_Plot_SectionEfficace()
{
  TGraph* GEANT4 = graph("Data_GEANT4.dat", 81, 1, 1e+22);
  TGraph* ENDF = graph("Data.dat", 85, 1e-6, 1);
  TGraph* IAEA = graph("IAEA_gx.dat", 88, 1e-6, 1);
  TGraph* ENDF_gxn = graph("Fe56_gxn.dat", 194, 1e-6, 1);
  TGraph* ENDF_gg = graph("Fe56_gg.dat", 27, 1e-6, 1);
  TGraph* ENDF_gn = graph("Fe56_gn.dat", 16, 1e-6, 1);
  TGraph* ENDF_g2n = graph("Fe56_g2n.dat", 7, 1e-6, 1);
  TGraph* ENDF_NON = graph("Fe56_NON.dat", 319, 1e-6, 1);
  TGraph* ENDF_gnp = graph("Fe56_gnp.dat", 7, 1e-6, 1);
  TGraph* ENDF_gna = graph("Fe56_gna.dat", 8, 1e-6, 1);
  TGraph* ENDFB7 = graph("ENDF-B7.dat", 45, 1e-6, 1);
  
  new TCanvas;
  //GEANT4->Draw();
  ENDFB7->Draw("");
  IAEA->Draw("same");
  GEANT4->SetLineColor(kRed);
  ENDFB7->SetLineColor(kBlue);
  IAEA->SetLineColor(kCyan);

  const int nfiles = 17;
  int variable =0;
  
  float E[nfiles] = {1, 2, 3, 4, 5, 10, 12, 14, 16, 17, 18, 19, 20, 25, 30, 40, 50};
  float e_E[nfiles] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float SE[nfiles]= {
		     section_efficace("Section_efficace_gn_Acier_1MeV.root", 100000000, variable),
		     section_efficace("Section_efficace_gn_Acier_2MeV.root", 100000000, variable),
		     section_efficace("Section_efficace_gn_Acier_3MeV.root", 100000000, variable),
		     section_efficace("Section_efficace_gn_Acier_4MeV.root", 100000000, variable),
		     section_efficace("Section_efficace_gn_Acier_5MeV.root", 100000000, variable),
		     section_efficace("Section_efficace_gn_Acier_10MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_13MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_14MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_16MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_17MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_18MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_19MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_20MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_25MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_30MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_40MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Acier_50MeV.root", 10000000, variable)};
  
  float e_SE[nfiles]= {
		       err_section_efficace("Section_efficace_gn_Acier_1MeV.root", 1000000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_2MeV.root", 1000000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_3MeV.root", 1000000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_4MeV.root", 1000000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_5MeV.root", 1000000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_10MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_13MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_14MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_16MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_17MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_18MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_19MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_20MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_25MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_30MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_40MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Acier_50MeV.root", 10000000, variable)};

  TGraphErrors *Sim = new TGraphErrors(nfiles, E, SE, e_E, e_SE);

  Sim->Draw("PESAME");
  Sim->SetLineColor(kBlack);
  //ENDF_gxn->Draw("same");
  //ENDF_gxn->SetLineColor(kGreen);



  new TCanvas;
  ENDF_NON->Draw("");
  ENDF_NON->SetLineColor(kOrange);
  ENDF_gxn->Draw("same");
  ENDF_gxn->SetLineColor(kRed);
  ENDF_gg->Draw("same");
  ENDF_gg->SetLineColor(kBlue);
  ENDF_gn->Draw("same");
  ENDF_gn->SetLineColor(kCyan);
  ENDF_g2n->Draw("same");
  ENDF_g2n->SetLineColor(kGreen);
  Sim->Draw("same");
  ENDF_gnp->Draw("same");
  ENDF_gnp->SetLineColor(kYellow);


  // new TCanvas;
  // ENDF_NON->Draw("");
  // ENDF_NON->SetLineColor(kOrange);
  // //JENDL->Draw("same");
  // //JENDL->SetLineColor(kBlue);
  // //ENDF_gg->Draw("same");
  // //ENDF_gg->SetLineColor(kBlue);
  // ENDF_gn->Draw("same");
  // ENDF_gn->SetLineColor(kCyan);
  // Sim->Draw("same");
  // ENDF_gnp->Draw("same");
  // ENDF_gnp->SetLineColor(kYellow);
  // ENDF_gna->Draw("same");
  // ENDF_gna->SetLineColor(kRed);
  // IAEA->Draw("same");
    
  

}
