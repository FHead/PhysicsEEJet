#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   vector<string> FileBases{"2jet", "inclusive"};

   for(string FileBase : FileBases)
   {
      TFile OutputFile(Form("Graph_%s.root", FileBase.c_str()), "RECREATE");

      TGraphAsymmErrors G;

      TFile InputFile(Form("%s.root", FileBase.c_str()));

      TTree *Tree = (TTree *)InputFile.Get("Tree");

      double XMin, XMax, YMin, YMax, Y;
      Tree->SetBranchAddress("XMin", &XMin);
      Tree->SetBranchAddress("XMax", &XMax);
      Tree->SetBranchAddress("YMin", &YMin);
      Tree->SetBranchAddress("YMax", &YMax);
      Tree->SetBranchAddress("Y",    &Y);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         double X = (XMin + XMax) / 2;

         G.SetPoint(iE, X, Y);
         G.SetPointError(iE, X - XMin, XMax - X, Y - YMin, YMax - Y);
      }

      InputFile.Close();

      G.SetNameTitle("GFelix", "G");

      OutputFile.cd();

      G.Write();

      OutputFile.Close();
   }

   return 0;
}




