#include <fstream>
#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input", "LEP2_merged.root");
   int Event             = CL.GetInteger("Event");
   int Run               = CL.GetInteger("Run");

   string OutputFileName = "txt/Particles_Run" + to_string(Run) + "_Event" + to_string(Event) + ".txt";
   ofstream out(OutputFileName);

   TFile File(InputFileName.c_str());

   TTree *T = (TTree *)File.Get("t");

   int EventNumber, RunNumber, Year;
   T->SetBranchAddress("EventNo", &EventNumber);
   T->SetBranchAddress("RunNo", &RunNumber);
   T->SetBranchAddress("year", &Year);

   float Energy, Thrust, TTheta, TPhi;
   T->SetBranchAddress("Energy", &Energy);
   T->SetBranchAddress("Thrust", &Thrust);
   T->SetBranchAddress("TTheta", &TTheta);
   T->SetBranchAddress("TPhi", &TPhi);
   
   int nParticle, nChargedParticle;
   float px[MAX], py[MAX], pz[MAX], mass[MAX];
   T->SetBranchAddress("nParticle", &nParticle);
   T->SetBranchAddress("nChargedHadronsHP", &nChargedParticle);
   T->SetBranchAddress("px", &px);
   T->SetBranchAddress("py", &py);
   T->SetBranchAddress("pz", &pz);
   T->SetBranchAddress("mass", &mass);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(RunNumber != Run)
         continue;
      if(EventNumber != Event)
         continue;

      cout << "Event found!" << endl;

      vector<PseudoJet> Particles;
      for(int iP = 0; iP < nParticle; iP++)
      {
         double E = sqrt(px[iP] * px[iP] + py[iP] * py[iP] + pz[iP] * pz[iP] + mass[iP] * mass[iP]);
         Particles.push_back(PseudoJet(px[iP], py[iP], pz[iP], E));
      }

      JetDefinition Definition(ee_genkt_algorithm, 0.4, -1);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> FastJets = sorted_by_E(Sequence.inclusive_jets());

      out << "# Run " << Run << ", Event = " << Event << endl;

      for(int iJ = 0; iJ < (int)FastJets.size(); iJ++)
      {
         out << "# Jet " << iJ << ", E = " << FastJets[iJ].e() << endl;

         int Color = iJ + 1;
         if(Color > 5)
            Color = 5;

         vector<PseudoJet> Constituents = FastJets[iJ].constituents();
         for(PseudoJet &P : Constituents)
            out << P.px() << " " << P.py() << " " << P.pz() << " " << Color << endl;
      }

      double L = 100;
      double LX = L * sin(TTheta) * cos(TPhi);
      double LY = L * sin(TTheta) * sin(TPhi);
      double LZ = L * cos(TTheta);

      out << "# Thrust: theta = " << TTheta << ", phi = " << TPhi << endl;
      out << LX << " " << LY << " " << LZ << " " << -1 << endl;
      out << -LX << " " << -LY << " " << -LZ << " " << -1 << endl;

      out << endl;
      out << endl;
      out << "=============" << endl;
      out << endl;
      out << endl;

      out << "Year = " << Year << "<br />" << endl;
      out << "Run = " << Run << ", Event = " << Event << "<br />" << endl;
      out << "NParticle = " << nParticle << " (" << nChargedParticle << " charged)<br />" << endl;
      out << "Thrust = " << Thrust << "<br />" << endl;
   }

   File.Close();

   out.close();

   return 0;
}


