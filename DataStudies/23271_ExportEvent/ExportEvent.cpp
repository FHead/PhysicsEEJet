#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName = CL.Get("input");
   string TreeName = CL.Get("tree", "t");
   string EventFile = CL.Get("eventlist");
   bool JetColor = CL.GetBool("jetcolor", false);
   double JetR = 0.4;

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   if(Tree == nullptr)
      return -1;

   vector<pair<double, double>> Events;

   ifstream in(EventFile);
   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');

      double Temp1 = -1, Temp2 = -1;
      stringstream str(ch);
      str >> Temp1 >> Temp2;

      if(Temp1 < 0 || Temp2 < 0)
         continue;

      Events.push_back(pair<double, double>(Temp1, Temp2));
   }

   int RunNo;
   int EventNo;
   int N;
   float M[10000];
   float PX[10000];
   float PY[10000];
   float PZ[10000];
   int PID[10000];
   short PWFlag[10000];

   Tree->SetBranchAddress("RunNo", &RunNo);
   Tree->SetBranchAddress("EventNo", &EventNo);
   Tree->SetBranchAddress("nParticle", &N);
   Tree->SetBranchAddress("mass", &M);
   Tree->SetBranchAddress("px", &PX);
   Tree->SetBranchAddress("py", &PY);
   Tree->SetBranchAddress("pz", &PZ);
   Tree->SetBranchAddress("pid", &PID);
   Tree->SetBranchAddress("pwflag", &PWFlag);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int EntryNumber = -1;
      for(int i = 0; i < (int)Events.size(); i++)
      {
         if(EventNo == Events[i].second && RunNo == Events[i].first)
         {
            EntryNumber = iE;
            break;
         }
      }
      if(EntryNumber < 0)
         continue;

      ofstream out(Form("Event_%d_%d.txt", RunNo, EventNo));

      vector<PseudoJet> FastJetParticles;
      for(int i = 0; i < N; i++)
      {
         FourVector P(0, PX[i], PY[i], PZ[i]);
         P[0] = sqrt(P.GetP() * P.GetP() + M[i] * M[i]);

         FastJetParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
      ClusterSequence Sequence(FastJetParticles, Definition);
      vector<PseudoJet> FastJets = sorted_by_E(Sequence.inclusive_jets(0.5));
      int NJet = FastJets.size();

      vector<FourVector> Jets;
      for(int i = 0; i < NJet; i++)
         Jets.push_back(FourVector(FastJets[i].e(), FastJets[i].px(), FastJets[i].py(), FastJets[i].pz()));

      if(JetColor == true)
      {
         out << "# 1 = leading jet" << endl;
         out << "# 2 = jet 2" << endl;
         out << "# 3 = jet 3" << endl;
         out << "# 4 = jet 4" << endl;
         out << "# 5 = others" << endl;
      }
      else
         out << "# Color = pwflag + 1" << endl;

      for(int i = 0; i < N; i++)
      {
         FourVector P(0, PX[i], PY[i], PZ[i]);
         P[0] = sqrt(P.GetP() * P.GetP() + M[i] * M[i]);

         if(P.GetP() < 1e-4)
            continue;

         int ClosestJet = -1;
         double ClosestAngle = -1;
         for(int i = 0; i < NJet; i++)
         {
            double Angle = GetAngle(Jets[i], P);
            if(Angle < ClosestAngle || ClosestAngle < 0)
            {
               ClosestJet = i;
               ClosestAngle = Angle;
            }
         }

         int ID = 0;
         
         if(JetColor == true)
         {
            if(ClosestAngle < JetR)
               ID = ClosestJet + 1;
            else
               ID = 5;

            if(ID >= 5)
               ID = 5;
         }
         else
            ID = PWFlag[i] + 1;

         out << PX[i] << " " << PY[i] << " " << PZ[i] << " " << ID << endl;
      }

      out.close();
   }

   File.Close();

   return 0;
}
