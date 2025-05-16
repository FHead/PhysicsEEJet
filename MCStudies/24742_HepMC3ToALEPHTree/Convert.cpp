#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "TauHelperFunctions3.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output", "Events.root");

   ifstream in(InputFileName.c_str());

   TFile File(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", "Converted from hepmc3");

   int EventNumber = 0;
   int NVertex = 0;
   int NParticle = 0;
   float Weight;
   float E[MAX];
   float PX[MAX];
   float PY[MAX];
   float PZ[MAX];
   float PT[MAX];
   float P[MAX];
   float Eta[MAX];
   float Theta[MAX];
   float Phi[MAX];
   float Mass[MAX];
   int PID[MAX];
   int Status[MAX];

   Tree.Branch("EventNo", &EventNumber, "&EventNo/I");
   Tree.Branch("nParticle", &NParticle, "nParticle/I");
   Tree.Branch("weight", &Weight, "weight/F");
   Tree.Branch("e", &E, "e[nParticle]/F");
   Tree.Branch("px", &PX, "px[nParticle]/F");
   Tree.Branch("py", &PY, "py[nParticle]/F");
   Tree.Branch("pz", &PZ, "pz[nParticle]/F");
   Tree.Branch("pt", &PT, "pt[nParticle]/F");
   Tree.Branch("pmag", &P, "pmag[nParticle]/F");
   Tree.Branch("eta", &Eta, "eta[nParticle]/F");
   Tree.Branch("theta", &Theta, "theta[nParticle]/F");
   Tree.Branch("phi", &Phi, "phi[nParticle]/F");
   Tree.Branch("mass", &Mass, "mass[nParticle]/F");
   Tree.Branch("pid", &PID, "pid[nParticle]/I");
   Tree.Branch("status", &Status, "status[nParticle]/I");

   bool InEvent = false;
   while(in)
   {
      char ch[10240];
      ch[0] = '\0';

      in.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      string Type = "";
      str >> Type;
      if(Type == "")
         continue;

      if(Type == "E")   // New event record
      {
         if(InEvent == false)
            InEvent = true;
         else
            Tree.Fill();

         str >> EventNumber >> NVertex >> NParticle;

         for(int i = 0; i < MAX; i++)
         {
            E[i] = 0;
            PX[i] = 0;
            PY[i] = 0;
            PZ[i] = 0;
            PT[i] = 0;
            P[i] = 0;
            Eta[i] = 0;
            Theta[i] = 0;
            Phi[i] = 0;
            Mass[i] = 0;
            PID[i] = 0;
            Status[i] = 0;
         }
      }
      else if(Type == "W")   // Weight
         str >> Weight;
      else if(Type == "U")   // unit information
      {
         // do nothing for now
      }
      else if(Type == "P")   // Particle record
      {
         int ID, V;
         str >> ID >> V;
         str >> PID[ID-1] >> PX[ID-1] >> PY[ID-1] >> PZ[ID-1] >> E[ID-1] >> Mass[ID-1] >> Status[ID-1];

         FourVector Particle(E[ID-1], PX[ID-1], PY[ID-1], PZ[ID-1]);
         PT[ID-1] = Particle.GetPT();
         P[ID-1] = Particle.GetP();
         Eta[ID-1] = Particle.GetEta();
         Theta[ID-1] = Particle.GetTheta();
         Phi[ID-1] = Particle.GetPhi();
      }
      else if(Type == "V")   // Vertex!
      {
         // do nothing for now
      }
      else if(Type == "A")   // HI information
      {
         // do nothing for now
      }
   }

   if(InEvent == true)
      Tree.Fill();

   File.cd();
   Tree.Write();

   File.Close();

   in.close();

   return 0;
}




