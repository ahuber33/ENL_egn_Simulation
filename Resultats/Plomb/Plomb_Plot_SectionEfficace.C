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
  cout << filename << endl;
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
  float A = 208.; //g/mol
  float Na = 6.022e+23; //mol-1
  float rho = 11.35; //g/cm-3
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
  float A = 208; //g/mol
  float Na = 6.022e+23; //mol-1
  float rho = 11.35; //g/cm-3
  float d = 0.01; //cm
  
  float section_efficace = ((A*p)/(Na*rho*d))*1e24;

  cout << "Section effiace [" << filename << "] = " << section_efficace << endl;
  //a->clear();
  
  return section_efficace;
}


void Plomb_Plot_SectionEfficace()
{
  //  TGraph* GEANT4 = graph("Data_GEANT4.dat", 81, 1, 1e+22);
  TGraph* JENDL = graph("Plomb_JENDL_new.dat", 369, 1e-6, 1);
  TGraph* IAEA = graph("Plomb_IAEA2019_new.dat", 87, 1e-6, 1);

  
  new TCanvas;
  //  GEANT4->Draw();
  IAEA->Draw("");
  JENDL->Draw("same");
  //  GEANT4->SetLineColor(kRed);
  JENDL->SetLineColor(kBlue);
  IAEA->SetLineColor(kCyan);

  const int nfiles = 13;
  int variable =0;
  
  float E[nfiles] = {10, 11, 12, 14, 16, 17, 18, 19, 20, 25, 30, 40, 50};
  float e_E[nfiles] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float SE[nfiles]= {
		     section_efficace("Section_efficace_gn_Plomb_10MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_11MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_12MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_14MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_16MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_17MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_18MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_19MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_20MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_25MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_30MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_40MeV.root", 10000000, variable),
		     section_efficace("Section_efficace_gn_Plomb_50MeV.root", 10000000, variable)};
  
  float e_SE[nfiles]= {
		       err_section_efficace("Section_efficace_gn_Plomb_10MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_11MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_12MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_14MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_16MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_17MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_18MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_19MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_20MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_25MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_30MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_40MeV.root", 10000000, variable),
		       err_section_efficace("Section_efficace_gn_Plomb_50MeV.root", 10000000, variable)};

  TGraphErrors *Sim = new TGraphErrors(nfiles, E, SE, e_E, e_SE);

  Sim->Draw("PESAME");
  Sim->SetLineColor(kBlack);

    
  

}
