#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "Pythia8/Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper4.h"
#include "GenparticleTree3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "CustomAssert.h"

#define MAX 10000

int main(int argc, char *argv[]);
void GenerateEvents(string OutputFileName, int NEvent, double EPythia, double EBall, double Mean, bool ExcludeE);
double DrawMomentum(double Mean);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string OutputFileName = CL.Get("Output");
   int N                 = CL.GetInt("N", 1000);
   double EPythia        = CL.GetDouble("EPythia", 91.1876);
   double EBall          = CL.GetDouble("EBall", 0);
   double Mean           = CL.GetDouble("Mean", 0.2);
   bool ExcludeE         = CL.GetBool("ExcludeE", false);

   Assert(EPythia >= 10 || EPythia <= 0, "Pythia does not support E < 10");

   GenerateEvents(OutputFileName, N, EPythia, EBall, Mean, ExcludeE);

   return 0;
}

void GenerateEvents(string OutputFileName, int NEvent, double EPythia, double EBall, double Mean, bool ExcludeE)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   int EventNo = 0;
   int RunNo = 1;
   int year = 2020;
   int subDir = 827;
   int process = 0;
   bool isMC = true;

   int nParticle;
   float e[MAX];
   float px[MAX];
   float py[MAX];
   float pz[MAX];
   float pt[MAX];
   float pmag[MAX];
   float rap[MAX];
   float eta[MAX];
   float theta[MAX];
   float phi[MAX];
   float mass[MAX];
   int subevent[MAX];
   // charge, pwflag
   int pid[MAX];
   int status[MAX];
   float vx[MAX];
   float vy[MAX];
   float vz[MAX];

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("tgen", "Tree! ®");

   OutputTree.Branch("EventNo", &EventNo, "EventNo/I");
   OutputTree.Branch("RunNo", &RunNo, "RunNo/I");
   OutputTree.Branch("year", &year, "year/I");
   OutputTree.Branch("subDir", &subDir, "subDir/I");
   OutputTree.Branch("process", &process, "process/I");
   OutputTree.Branch("isMC", &isMC, "isMC/O");
   OutputTree.Branch("EPythia", &EPythia, "EPythia/D");
   OutputTree.Branch("EBall", &EBall, "EBall/D");

   OutputTree.Branch("nParticle", &nParticle, "nParticle/I");
   OutputTree.Branch("e", &e, "e[nParticle]/F");
   OutputTree.Branch("px", &px, "px[nParticle]/F");
   OutputTree.Branch("py", &py, "py[nParticle]/F");
   OutputTree.Branch("pz", &pz, "pz[nParticle]/F");
   OutputTree.Branch("pt", &pt, "pt[nParticle]/F");
   OutputTree.Branch("pmag", &pmag, "pmag[nParticle]/F");
   OutputTree.Branch("rap", &rap, "rap[nParticle]/F");
   OutputTree.Branch("eta", &eta, "eta[nParticle]/F");
   OutputTree.Branch("theta", &theta, "theta[nParticle]/F");
   OutputTree.Branch("phi", &phi, "phi[nParticle]/F");
   OutputTree.Branch("mass", &mass, "mass[nParticle]/F");
   OutputTree.Branch("subevent", &subevent, "subevent[nParticle]/I");
   OutputTree.Branch("pid", &pid, "pid[nParticle]/I");
   OutputTree.Branch("status", &status, "status[nParticle]/I");
   OutputTree.Branch("vx", &vx, "vx[nParticle]/F");
   OutputTree.Branch("vy", &vy, "vy[nParticle]/F");
   OutputTree.Branch("vz", &vz, "vz[nParticle]/F");

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Tune:pp 14");                        // Tune?  What??
   pythia.readString("Tune:ee 7");                         // I see this in CMS production settings.....

   pythia.readString("WeakBosonExchange:all = on");
   pythia.readString("WeakSingleBoson:all = on");

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.readString("Beams:idA = 11");                    // electron
   pythia.readString("Beams:idB = -11");                   // positron
   pythia.readString(Form("Beams:eCM = %f", EPythia));     // Collision energy from input

   pythia.readString("Next:numberCount = 0");              // how often to print to screen on progress
   pythia.readString("Next:numberShowProcess = 0");        // do we print first hard process?  No!
   pythia.readString("Next:numberShowEvent = 0");          // do we print first event?  No!

   pythia.init();

   for(int iEntry = 0; iEntry < NEvent; iEntry++)
   {
      EventNo = iEntry;

      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << NEvent << endl;

      if(EPythia >= 10)
      {
         // Generate event
         pythia.next();

         // Particles
         vector<GenParticle> Particles(pythia.event.size());

         // Loop over particles
         for(int j = 0; j < pythia.event.size(); j++)
         {
            Particles[j].P[0] = pythia.event[j].e();
            Particles[j].P[1] = pythia.event[j].px();
            Particles[j].P[2] = pythia.event[j].py();
            Particles[j].P[3] = pythia.event[j].pz();

            Particles[j].V[0] = pythia.event[j].tProd();
            Particles[j].V[1] = pythia.event[j].xProd();
            Particles[j].V[2] = pythia.event[j].yProd();
            Particles[j].V[3] = pythia.event[j].zProd();

            Particles[j].PDGID = pythia.event[j].id();
            Particles[j].StatusCode = pythia.event[j].statusHepMC();

            Particles[j].Mothers = pythia.event[j].motherList();
            Particles[j].Daughters = pythia.event[j].daughterList();
         }
         GenParticleTree Tree(Particles, 1, iEntry + 1);

         if(ExcludeE == true)
         {
            // Check event type
            vector<int> Strong;
            vector<int> Final;
            for(int i = 0; i < Tree.ParticleCount(); i++)
            {
               if(Tree[i].StatusCode == 1)
                  Final.push_back(abs(Tree[i].PDGID));
               if(Tree[i].P.GetP() > EPythia * 0.5 * 0.90)
                  if(Tree[i].P.GetTheta() > 0.01 * M_PI && Tree[i].P.GetTheta() < 0.99 * M_PI)
                     Strong.push_back(abs(Tree[i].PDGID));
            }

            sort(Final.begin(), Final.end());
            Final.erase(unique(Final.begin(), Final.end()), Final.end());
            if(Final.size() == 2 && Final[0] == 11 && Final[1] == 22)   // Crazy electron event!  skip!
            {
               iEntry = iEntry - 1;
               continue;
            }
            
            // sort(Strong.begin(), Strong.end());
            // Strong.erase(unique(Strong.begin(), Strong.end()), Strong.end());
            // if(Strong.size() > 0 && Strong[0] == 11)   // this is an electron event!  skip!
            // {
            //    iEntry = iEntry - 1;
            //    continue;
            // }
         }

         // Write particles into tree
         nParticle = pythia.event.size();
         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            e[i]        = Tree[i].P[0];
            px[i]       = Tree[i].P[1];
            py[i]       = Tree[i].P[2];
            pz[i]       = Tree[i].P[3];
            pt[i]       = Tree[i].P.GetPT();
            pmag[i]     = Tree[i].P.GetP();
            rap[i]      = Tree[i].P.GetY();
            eta[i]      = Tree[i].P.GetEta();
            theta[i]    = Tree[i].P.GetTheta();
            phi[i]      = Tree[i].P.GetPhi();
            mass[i]     = Tree[i].P.GetMass();
            subevent[i] = 0;
            pid[i]      = Tree[i].PDGID;
            status[i]   = Tree[i].StatusCode;
            vx[i]       = Tree[i].V[1];
            vy[i]       = Tree[i].V[2];
            vz[i]       = Tree[i].V[3];
         }
      }
      else
         nParticle = 0;

      // Generate the "ball"
      double ParticleMass = 0.13957;  // pion mass
      double ParticleMean = Mean;     // mean momentum for the thermal distribution

      // Step 1 of generating the ball: get a list of particles with total mass equals to EBall
      vector<FourVector> BallParticles;
      FourVector Total(0, 0, 0, 0);
      bool Done = false;
      while(Total.GetMass() < EBall)
      {
         double Momentum = DrawMomentum(ParticleMean);
         double Phi = DrawRandom(0, 2 * M_PI);
         double Theta = DrawSine(0, M_PI);
         FourVector P;
         P.SetSizeThetaPhiMass(Momentum, Theta, Phi, ParticleMass);

         if((Total + P).GetMass() >= EBall)
         {
            if((Total + FourVector(ParticleMass, 0, 0, 0)).GetMass() > EBall)
               P = FourVector(ParticleMass, 0, 0, 0);
            else
            {
               // Solve for the momentum
               double M0 = (Total + FourVector(ParticleMass, 0, 0, 0)).GetMass();
               double M1 = (Total + P).GetMass();
               double P0 = 0;
               double P1 = Momentum;

               double Tolerance = 0.000001;
               while(M1 - M0 > Tolerance)
               {
                  double P2 = (P0 + P1) / 2;
                  P.SetSizeThetaPhiMass(P2, Theta, Phi, ParticleMass);
                  double M2 = (Total + P).GetMass();

                  if(M2 < EBall)
                     P0 = P2, M0 = M2;
                  else
                     P1 = P2, M1 = M2;
               }
            }

            Done = true;
         }
            
         BallParticles.push_back(P);
         Total = Total + P;

         if(Done == true)
            break;
      }

      // Step 2 of generating the ball: boost everything back to ball-rest-frame
      double BoostGamma = Total[0] / EBall;
      for(int i = 0; i < (int)BallParticles.size(); i++)
         BallParticles[i] = BallParticles[i].GammaBoost(-Total, BoostGamma);

      // Step 3 of generating the ball: write things out!
      for(int i = 0; i < (int)BallParticles.size(); i++)
      {
         e[i+nParticle]        = BallParticles[i][0];
         px[i+nParticle]       = BallParticles[i][1];
         py[i+nParticle]       = BallParticles[i][2];
         pz[i+nParticle]       = BallParticles[i][3];
         pt[i+nParticle]       = BallParticles[i].GetPT();
         pmag[i+nParticle]     = BallParticles[i].GetP();
         rap[i+nParticle]      = BallParticles[i].GetY();
         eta[i+nParticle]      = BallParticles[i].GetEta();
         theta[i+nParticle]    = BallParticles[i].GetTheta();
         phi[i+nParticle]      = BallParticles[i].GetPhi();
         mass[i+nParticle]     = BallParticles[i].GetMass();
         subevent[i+nParticle] = 1;
         pid[i+nParticle]      = 211;
         status[i+nParticle]   = 1;
         vx[i+nParticle]       = 0;
         vy[i+nParticle]       = 0;
         vz[i+nParticle]       = 0;
      }
      nParticle = nParticle + BallParticles.size();

      /*
      // Group into jets - also calculate MET along the way
      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // final particles only
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16 || Tree[i].PDGID == 14 || Tree[i].PDGID == -14
            || Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(Tree[i].P).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(Tree[i].P).GetPT() < 1)   // mini particles - forget it
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         MissingEnergy = MissingEnergy - FourVector(Tree[i].P);
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.4
      */

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();
}

double DrawMomentum(double Mean)
{
   double a = 2 / Mean;
   double X;

   double Max = Mean * 20;

   bool Good = false;
   while(Good == false)
   {
      X = DrawExponential(-a, 0);
      if(X < Max && DrawRandom(0, 1) < X / Max)
         Good = true;
   }

   return X;
}
