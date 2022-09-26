void Test()
{

  TFile* file = new TFile("150MeV_e_Tungstene_1cm.root");
  TTree* Tree = (TTree*)file->Get("theRunTree");
  int Entries = Tree->GetEntries();
  vector<float>* E =0;
  Tree->SetBranchAddress("EBremPlaque", &E);
  TH1F* Brem = new TH1F("Brem", "Brem", 200, 0, 200000);

  for (int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      //cout << "size = " << E->size() << endl;
      for (int j=0; j<E->size(); j++)
	{
	  Brem->Fill(E->at(j));
	}
    }

  //file->Close();


  TFile* filenew = new TFile("Brem_Exit_Plaque_150MeV_e_Tungstene_10mm.root", "recreate");
  Brem->Draw();
  Brem->Write();
  filenew->Close();
  
}
