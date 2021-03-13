#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName = CL.Get("input");
   string TreeName = CL.Get("tree", "tgen");
   int EventNumber = CL.GetInt("n");

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   if(Tree == nullptr)
      return -1;

   int N;
   float PX[10000];
   float PY[10000];
   float PZ[10000];
   int Status[10000];
   int SubEvent[10000];
   int PID[10000];

   Tree->SetBranchAddress("nParticle", &N);
   Tree->SetBranchAddress("px", &PX);
   Tree->SetBranchAddress("py", &PY);
   Tree->SetBranchAddress("pz", &PZ);
   Tree->SetBranchAddress("status", &Status);
   Tree->SetBranchAddress("subevent", &SubEvent);
   Tree->SetBranchAddress("pid", &PID);

   if(EventNumber < 0)
      return -1;
   if(EventNumber >= Tree->GetEntries())
      return -1;

   Tree->GetEntry(EventNumber);

   cout << "# 1 = ball" << endl;
   cout << "# 2 = lepton" << endl;
   cout << "# 3 = photon" << endl;
   cout << "# 4 = PID > 100" << endl;
   cout << "# 5 = neutrino" << endl;
   cout << "# 6 = other" << endl;

   for(int i = 0; i < N; i++)
   {
      double P = sqrt(PX[i] * PX[i] + PY[i] * PY[i] + PZ[i] * PZ[i]);
      if(P < 1e-4)
         continue;

      if(Status[i] == 1)
      {
         int ID = 0;
         if(SubEvent[i] == 1)
            ID = 1;
         else
         {
            if(PID[i] == 11 || PID[i] == -11)
               ID = 2;
            else if(PID[i] == 13 || PID[i] == -13)
               ID = 2;
            else if(PID[i] == 15 || PID[i] == -15)
               ID = 2;
            else if(PID[i] == 22)
               ID = 3;
            else if(PID[i] > 100 || PID[i] < -100)
               ID = 4;
            else if(PID[i] == 12 || PID[i] == -12)
               ID = 5;
            else if(PID[i] == 14 || PID[i] == -14)
               ID = 5;
            else if(PID[i] == 16 || PID[i] == -16)
               ID = 5;
            else
               ID = 6;
         }

         if(ID == 6)
            cout << "#" << PID[i] << endl;
         cout << PX[i] << " " << PY[i] << " " << PZ[i] << " " << ID << endl;
      }
   }

   File.Close();

   return 0;
}
