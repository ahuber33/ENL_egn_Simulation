#include <iostream>
#include <fstream>

using namespace std;


TH1F* histo(const char* filename, const int nlines, int nstart, int nend)
{

  TH1F* histo = new TH1F(filename, filename, nlines, nstart, nend);
  ifstream file(filename);
  float E[nlines], N[nlines];
  float Sum=0;

  for (int i=0; i<nlines; i++)
    {
      file >> E[i] >> N[i];
      //      cout << E[i] << " " << N[i] << endl;
      histo->SetBinContent(i, N[i]);
      if(N[i] >0){Sum+=N[i];}
      }
  file.close();

  cout << "Sum [" << filename << "] = " << Sum << endl;
  
  return histo;
}


TGraph* graph(const char* filename, const int nlines)
{

  ifstream file(filename);
  float E[nlines], N[nlines];

  for (int i=0; i<2500; i++)
    {
      file >> E[i] >> N[i];
      //      cout << E[i] << " " << N[i] << endl;
    }
  file.close();

  TGraph* graph = new TGraph(nlines, E, N);

  return graph;
}

void Plot()
{

  const int nlines = 2500;
  TGraph* scan1 = graph("scan08_1_SPECTR.txt", nlines);
  TH1F* scan1_h = histo("scan08_1_SPECTR.txt", nlines, 556, 49513);
  //TGraph* scan2 = graph("scan08_2_SPECTR.txt", nlines);
  //  TGraph* scan5 = graph("scan08_5_SPECTR.txt", nlines);
  scan1->Draw();
  scan1_h->Draw("same");
  //scan2->Draw("same");
  //  scan5->Draw("same");
  scan1->SetLineColor(kRed);
  //scan2->SetLineColor(kCyan);
  //  scan5->SetLineColor(kBlack);
  scan1_h->Rebin(4);

  

  ofstream ofile("Spectre_scan08_1.txt");
   float a;
  
     for(int i =0; i<625; i++)
       {
         a= scan1_h->GetBinContent(i+1);
	 //         if (a<0){a=0.1;}
         ofile <<scan1_h->GetBinCenter(i+1)/1000 << " " << a/5.97828e+09 << endl;
       }
  
}
