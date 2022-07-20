void Conversion_ENDF_file()
{
  //ifstream file("Alu/Alu_JENDL.dat");
  //ifstream file("Cuivre/Cuivre_IAEA2019.dat");
  ifstream file("Tungstene/Tungstene_IAEA2019.dat");
  float E[1000], CS[1000];
  float junk;
  int n=0;
  
  for (int i=0; i<27; i++)
    {
      file >> E[n] >> CS[n] >> E[n+1] >> CS[n+1] >> E[n+2] >> CS[n+2] >> junk;
      cout << "E[" << n << "] = " << E[n]  << endl;
      cout << "CS[" << n << "] = " << CS[n]  << endl;
      cout << "E[" << n+1 << "] = " << E[n+1]  << endl;
      cout << "CS[" << n+1 << "] = " << CS[n+1]  << endl;
      cout << "E[" << n+2 << "] = " << E[n+2]  << endl;
      cout << "CS[" << n+2 << "] = " << CS[n+2]  << endl;
      cout << "junk = " << junk << endl;
      n+=3;
    }
  file.close();

  //ofstream efile("Alu/Alu_JENDL_new.dat");
  //ofstream efile("Cuivre/Cuivre_IAEA2019_new.dat");
  ofstream efile("Tungstene/Tungstene_IAEA2019_new.dat");
  for (int i=0; i<n; i++)
    {
      efile << E[i] << " " << CS[i] << endl;
    }
  efile.close();
  
}
