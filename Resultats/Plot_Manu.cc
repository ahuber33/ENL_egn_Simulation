void Plot_Manu()
{

  TFile* file = new TFile("a.root");
  TTree* Tree = (TTree*)file->Get("theRunTree");
  int Entries = Tree->GetEntries();
  cout << "Entries = " << Entries << endl;

  std::vector<float>* Edep=0;
  std::vector<float>* z=0;
  Tree->SetBranchAddress("E_elec_Deposit", &Edep);
  Tree->SetBranchAddress("Position_Deposit", &z);

  TH1F *h_Edep = new TH1F("Edep", "Edep", 200, 0, 2000);
  TH1F *h_Position = new TH1F("Position", "Position", 200, 0, 2);
  TH2F* h_Edep_z = new TH2F("Edep vs z", "Edep vs z", 200, 0, 2, 200, 0, 2000);
  TH1F *h_Integral_Edep_z = new TH1F("Edep_z", "Edep_z", 200, 0, 2);
  int bin=0;

    for(int i=0; i<Entries; i++)
    {
      Edep->clear();
      z->clear();
      Tree->GetEntry(i);
      
      for (int j=0; j<Edep->size(); j++)
	{
	  h_Edep->Fill(Edep->at(j));
	  h_Position->Fill(z->at(j));
	  h_Edep_z->Fill(z->at(j), Edep->at(j));
	  bin = z->at(j)*100;
	  cout << "z = " << z->at(j) << endl;
	  cout << "bin = " << bin << endl;
	  h_Integral_Edep_z->SetBinContent(bin, h_Integral_Edep_z->GetBinContent(bin) + Edep->at(j));
	}
    }


    new TCanvas;
    h_Edep->Draw();

    new TCanvas;
    h_Position->Draw();

    new TCanvas;
    h_Edep_z->Draw("colz");

    new TCanvas;
    h_Integral_Edep_z->Draw();
      
  
}
