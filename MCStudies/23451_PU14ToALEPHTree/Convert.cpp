#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 100000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   ifstream in(InputFileName);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("t", "tree from pu14");

   int EventNumber = 0;
   int NParticle = 0;
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
   
   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream strpeek(ch);
      string ID = "";
      strpeek >> ID;

      if(ID == "#")
         continue;

      if(ID == "end")
      {
         Tree.Fill();
         NParticle = 0;
         EventNumber = EventNumber + 1;
         continue;
      }

      stringstream str(ch);
      double px, py, pz, m, id, v;
      str >> px >> py >> pz >> m >> id >> v;

      FourVector V(0, px, py, pz);
      V[0] = sqrt(V.GetP() * V.GetP() + m * m);

      E[NParticle] = V[0];
      PX[NParticle] = V[1];
      PY[NParticle] = V[2];
      PZ[NParticle] = V[3];
      PT[NParticle] = V.GetPT();
      P[NParticle] = V.GetP();
      Eta[NParticle] = V.GetEta();
      Theta[NParticle] = V.GetTheta();
      Phi[NParticle] = V.GetPhi();
      Mass[NParticle] = V.GetMass();
      PID[NParticle] = id;
      if(v != 0)
         Status[NParticle] = -v;
      else
         Status[NParticle] = 1;

      NParticle = NParticle + 1;
   }

   Tree.Write();
   OutputFile.Close();

   return 0;
}



