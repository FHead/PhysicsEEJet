#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"

#include "CommandLine.h"
#include "ProgressBar.h"

#include "JetCorrector.h"

#define MAX 1000

int main(int argc, char *argv[]);
double EtaToTheta(double Eta);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName   = CL.Get("Input");
   string OutputFileName  = CL.Get("Output");
   string InputTreeName   = CL.Get("Tree");
   vector<string> JECFile = CL.GetStringVector("JEC", vector<string>());
   double Fraction        = CL.GetDouble("Fraction", 1.00);

   JetCorrector JEC(JECFile);

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());

   int N;
   int JetN[MAX];
   float JetRawPT[MAX], JetPT[MAX], JetEta[MAX], JetPhi[MAX], JetM[MAX], JetTheta[MAX], JetE[MAX], JetRawE[MAX];
   InputTree->SetBranchAddress("nref", &N);
   InputTree->SetBranchAddress("jtpt", &JetRawPT);
   InputTree->SetBranchAddress("jteta", &JetEta);
   InputTree->SetBranchAddress("jtphi", &JetPhi);
   InputTree->SetBranchAddress("jtm", &JetM);
   InputTree->SetBranchAddress("jtN", &JetN);

   TTree OutputTree("Tree", "Processed trees");

   OutputTree.Branch("N",        &N,        "N/I");
   OutputTree.Branch("JetPT",    &JetPT,    "JetPT[N]/F");
   OutputTree.Branch("JetRawPT", &JetRawPT, "JetRawPT[N]/F");
   OutputTree.Branch("JetEta",   &JetEta,   "JetEta[N]/F");
   OutputTree.Branch("JetTheta", &JetTheta, "JetTheta[N]/F");
   OutputTree.Branch("JetPhi",   &JetPhi,   "JetPhi[N]/F");
   OutputTree.Branch("JetM",     &JetM,     "JetM[N]/F");
   OutputTree.Branch("JetN",     &JetN,     "JetN[N]/I");
   OutputTree.Branch("JetE",     &JetE,     "JetE[N]/F");
   OutputTree.Branch("JetRawE",  &JetRawE,  "JetRawE[N]/F");

   int EntryCount = InputTree->GetEntries();
   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount * Fraction; iE++)
   {
      Bar.Update(iE);
      if(EntryCount < 1000 || iE % (EntryCount / 300) == 0)
         Bar.Print();

      InputTree->GetEntry(iE);

      for(int i = 0; i < N; i++)
      {
         double Momentum = JetRawPT[i] * cosh(JetEta[i]);
         double Energy = sqrt(Momentum * Momentum + JetM[i] * JetM[i]);

         JetTheta[i] = EtaToTheta(JetEta[i]);

         JEC.SetJetE(Energy);
         JEC.SetJetP(Momentum);
         JEC.SetJetTheta(JetTheta[i]);
         JEC.SetJetPhi(JetPhi[i]);

         JetPT[i] = JetRawPT[i] * JEC.GetCorrection();
         JetRawE[i] = Energy;
         JetE[i] = Energy * JEC.GetCorrection();
      }

      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}

double EtaToTheta(double Eta)
{
   double x = exp(-2 * fabs(Eta));

   double y = (1 - x) / (1 + x);

   double Theta = acos(y);

   if(Eta < 0)
      Theta = M_PI - Theta;

   return Theta;
}



