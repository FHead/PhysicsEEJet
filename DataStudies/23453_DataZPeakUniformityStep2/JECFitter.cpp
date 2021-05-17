#include <map>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "DataHelper.h"

#define MAX 30
#define MAXPARAMETER 10
#define MAXMASS 150
#define MINMASS 20

struct Event;
class AllEvent;
int main(int argc, char *argv[]);

struct Event
{
   int N;
   double PX[MAX], PY[MAX], PZ[MAX], E[MAX];
};

class AllEvent
{
public:
   vector<Event> EData;
   vector<Event> EMC;
   map<int, vector<double>> MMC;
   double PCut;
   int NJet;
   enum {Const, Linear, Quadratic, Cubic, Quartic, Cintic} FunctionType;
public:
   AllEvent();
   AllEvent(string FileNameMC, string FileNameData, double MinimumP = 5, int MaximumN = 3, double Percentage = 1);
   void Initialize(string FileNameMC, string FileNameData, double MinimumP = 5, int MaximumN = 3, double Percentage = 1);
   void ReadFile(vector<Event> &E, string FileName, double Percentage = 1);
   map<int, vector<double>> GetMass(const vector<Event> &E, bool ApplyJEC, const double *Parameters) const;
   int GetBin(double Theta) const;
   double GetJEC(double P, double Theta, const double *Parameters) const;
   double Likelihood(const double *Parameters);
   const double *DoFit();
};

AllEvent::AllEvent()
{
}

AllEvent::AllEvent(string FileNameMC, string FileNameData, double MinimumP, int MaximumN, double Percentage)
{
   Initialize(FileNameMC, FileNameData, MinimumP, MaximumN);
}

void AllEvent::Initialize(string FileNameMC, string FileNameData, double MinimumP, int MaximumN, double Percentage)
{
   PCut = MinimumP;
   NJet = MaximumN;

   ReadFile(EMC, FileNameMC, Percentage);
   ReadFile(EData, FileNameData, Percentage);

   MMC = GetMass(EMC, false, nullptr);
   for(auto &i : MMC)
      sort(i.second.begin(), i.second.end());
}

void AllEvent::ReadFile(vector<Event> &E, string FileName, double Percentage)
{
   E.clear();

   TFile File(FileName.c_str());

   int N;
   float JetPT[MAX], JetEta[MAX], JetPhi[MAX], JetM[MAX];
   float JetTheta[MAX];

   TTree *Tree = (TTree *)File.Get("Tree");
   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("JetM", &JetM);
   Tree->SetBranchAddress("JetTheta", &JetTheta);

   int EntryCount = Tree->GetEntries() * Percentage;
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      Event NewEvent;

      NewEvent.N = N;
      for(int j = 0; j < N; j++)
      {
         if(JetTheta[j] < 0.15 * M_PI || JetTheta[j] > 0.85 * M_PI)
            JetPT[j] = 0;

         NewEvent.PX[j] = JetPT[j] * cos(JetPhi[j]);
         NewEvent.PY[j] = JetPT[j] * sin(JetPhi[j]);
         NewEvent.PZ[j] = JetPT[j] * sinh(JetEta[j]);
         NewEvent.E[j] = sqrt((JetPT[j] * cosh(JetEta[j]) * JetPT[j] * cosh(JetEta[j])) + JetM[j] * JetM[j]);
         // NewEvent.E[j] = JetPT[j] * cosh(JetEta[j]);
      }

      E.push_back(NewEvent);
   }

   File.Close();
}

map<int, vector<double>> AllEvent::GetMass(const vector<Event> &E, bool ApplyJEC, const double *Parameters) const
{
   map<int, vector<double>> Result;
   Result.insert(pair<int, vector<double>>(0, vector<double>()));
   Result.insert(pair<int, vector<double>>(1, vector<double>()));
   Result.insert(pair<int, vector<double>>(2, vector<double>()));
   Result.insert(pair<int, vector<double>>(3, vector<double>()));
   Result.insert(pair<int, vector<double>>(4, vector<double>()));
   Result.insert(pair<int, vector<double>>(5, vector<double>()));

   for(int i = 0; i < (int)E.size(); i++)
   {
      double LeadingP = -1;
      double LeadingTheta = 0.5 * M_PI;

      double SumE = 0, SumX = 0, SumY = 0, SumZ = 0;
      int JetCount = 0;
      for(int j = 0; j < E[i].N; j++)
      {
         double P = sqrt(E[i].PX[j] * E[i].PX[j] + E[i].PY[j] * E[i].PY[j] + E[i].PZ[j] * E[i].PZ[j]);
         if(P < 0.001)
            continue;
         double Theta = acos(E[i].PZ[j] / P);
         double JEC = (ApplyJEC ? GetJEC(P, Theta, Parameters) : 1);
         if(sqrt(E[i].PX[j] * E[i].PX[j] + E[i].PY[j] * E[i].PY[j]) * JEC < PCut)
            continue;
         SumE = SumE + E[i].E[j]  * JEC;
         SumX = SumX + E[i].PX[j] * JEC;
         SumY = SumY + E[i].PY[j] * JEC;
         SumZ = SumZ + E[i].PZ[j] * JEC;
         JetCount = JetCount + 1;

         if(P > LeadingP || LeadingP < 0)
         {
            LeadingP = P;
            LeadingTheta = Theta;
         }
      }
      double M2 = SumE * SumE - SumX * SumX - SumY * SumY - SumZ * SumZ;
      if(M2 < MINMASS * MINMASS || M2 > MAXMASS * MAXMASS)
         continue;
      if(JetCount > NJet)
         continue;

      int Bin = GetBin(LeadingTheta);
      Result[Bin].push_back(M2);
   }

   return Result;
}

int AllEvent::GetBin(double Theta) const
{
   if(Theta < 0.25 * M_PI)
      return 0;
   if(Theta < 0.30 * M_PI)
      return 1;
   if(Theta < 0.35 * M_PI)
      return 2;
   if(Theta < 0.40 * M_PI)
      return 3;
   if(Theta < 0.45 * M_PI)
      return 4;
   if(Theta < 0.50 * M_PI)
      return 5;
   if(Theta < 0.55 * M_PI)
      return 5;
   if(Theta < 0.60 * M_PI)
      return 4;
   if(Theta < 0.65 * M_PI)
      return 3;
   if(Theta < 0.70 * M_PI)
      return 2;
   if(Theta < 0.75 * M_PI)
      return 1;
   return 0;
}

double AllEvent::GetJEC(double P, double Theta, const double *Parameters) const
{
   if(Parameters == nullptr)
      return 1;

   // Clipping
   if(P < PCut)   P = PCut;

   double Overall = Parameters[GetBin(Theta)];

   if(FunctionType == Const)
      return Overall;
   if(FunctionType == Linear)
      return Overall * (1 + Parameters[6] * P);
   if(FunctionType == Quadratic)
      return Overall * (1 + Parameters[6] * P + Parameters[7] * P * P);
   if(FunctionType == Cubic)
      return Overall * (1 + Parameters[6] * P + Parameters[7] * P * P + Parameters[8] * P * P * P);
   if(FunctionType == Quartic)
      return Overall * (1 + Parameters[6] * P + Parameters[7] * P * P + Parameters[8] * P * P * P + Parameters[9] * P * P * P * P);
   if(FunctionType == Cintic)
      return Overall * (1 + Parameters[6] * P + Parameters[7] * P * P + Parameters[8] * P * P * P + Parameters[9] * P * P * P * P + Parameters[10] * P * P * P * P * P);

   return 1;
}

double AllEvent::Likelihood(const double *Parameters)
{
   double LL = 0;

   map<int, vector<double>> MData = GetMass(EData, true, Parameters);
   for(auto &i : MData)
      sort(i.second.begin(), i.second.end());

   // This is quantile distance
   // int N = 20;
   // for(int i = 5; i < N; i++)
   // {
   //    // cout << "   " << i << " " << sqrt(MMC[MMC.size()*i/N]) << " " << sqrt(MData[MData.size()*i/N]) << endl;
   //    double Delta = sqrt(MMC[MMC.size()*i/N]) - sqrt(MData[MData.size()*i/N]);
   //    LL = LL + Delta * Delta / (MAXMASS - MINMASS);
   // }

   // This is quantile mean
   int N = 50;
   for(int iB = 0; iB < 6; iB++)
   {
      for(int i = 5; i < N - 5; i++)
      {
         double SumMC = 0, SumData = 0;
         int CountMC = MMC[iB].size() / N, CountData = MData[iB].size() / N;
         for(int j = CountMC * i; j < CountMC * (i + 1); j++)
            SumMC = SumMC + sqrt(MMC[iB][j]);
         for(int j = CountData * i; j < CountData * (i + 1); j++)
            SumData = SumData + sqrt(MData[iB][j]);
         double Delta = SumMC / CountMC - SumData / CountData;
         LL = LL + Delta * Delta / (MAXMASS - MINMASS);
         // cout << "   " << i << " " << SumMC / CountMC << " " << SumData / CountData << endl;
      }
   }

   // cout << Parameters[0] << " " << LL << endl;

   return LL;
}

const double *AllEvent::DoFit()
{
   ROOT::Math::Minimizer *Minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   Minimizer->SetMaxFunctionCalls(100000);
   Minimizer->SetMaxIterations(10000);
   Minimizer->SetTolerance(0.0001);
   Minimizer->SetPrintLevel(1);

   int N = 1;
   if(FunctionType == Const)       N = 6;
   if(FunctionType == Linear)      N = 7;
   if(FunctionType == Quadratic)   N = 8;
   if(FunctionType == Cubic)       N = 9;
   if(FunctionType == Quartic)     N = 10;
   if(FunctionType == Cintic)      N = 11;

   ROOT::Math::Functor F(this, &AllEvent::Likelihood, N);
   Minimizer->SetFunction(F);

   Minimizer->SetLimitedVariable(0, "JECT0", 1.00, 0.1, 0.5, 1.5);
   Minimizer->SetLimitedVariable(1, "JECT1", 1.00, 0.1, 0.5, 1.5);
   Minimizer->SetLimitedVariable(2, "JECT2", 1.00, 0.1, 0.5, 1.5);
   Minimizer->SetLimitedVariable(3, "JECT3", 1.00, 0.1, 0.5, 1.5);
   Minimizer->SetLimitedVariable(4, "JECT4", 1.00, 0.1, 0.5, 1.5);
   Minimizer->SetLimitedVariable(5, "JECT5", 1.00, 0.1, 0.5, 1.5);

   if(N > 6)    Minimizer->SetLimitedVariable(6, "JEC1", -0.000250851, 0.1, -1.0, 1.0);
   if(N > 7)    Minimizer->SetLimitedVariable(7, "JEC2", 3.8746e-6, 0.1, -1.0, 1.0);
   if(N > 8)    Minimizer->SetLimitedVariable(8, "JEC3", 1.64795e-7, 0.1, -1.0, 1.0);
   if(N > 9)    Minimizer->SetLimitedVariable(9, "JEC4", 4.15447e-10, 0.1, -1.0, 1.0);
   if(N > 10)   Minimizer->SetLimitedVariable(10, "JEC5", -6.8848e-11, 0.1, -1.0, 1.0);

   Minimizer->Minimize();

   return Minimizer->X();
}

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileNameMC   = CL.Get("MC");
   string FileNameData = CL.Get("Data");
   string Validation   = CL.Get("Validation", "FitValidation.pdf");
   string State        = CL.Get("State",      "DefaultState");
   string DHFileName   = CL.Get("DHFile",     "FitResults.dh");

   double PCut         = CL.GetDouble("PCut", 5);
   int NJet            = CL.GetInt("NJet",    3);
   double Percentage   = CL.GetDouble("Percentage", 1.00);

   AllEvent Events(FileNameMC, FileNameData, PCut, NJet, Percentage);
   
   Events.FunctionType = AllEvent::Const;
   const double *Parameter0 = Events.DoFit();
   Events.FunctionType = AllEvent::Linear;
   const double *Parameter1 = Events.DoFit();
   // Events.FunctionType = AllEvent::Quadratic;
   // const double *Parameter2 = Events.DoFit();
   // Events.FunctionType = AllEvent::Cubic;
   // const double *Parameter3 = Events.DoFit();
   // Events.FunctionType = AllEvent::Quartic;
   // const double *Parameter4 = Events.DoFit();
   // Events.FunctionType = AllEvent::Cintic;
   // const double *Parameter5 = Events.DoFit();

   DataHelper DHFile(DHFileName);

   DHFile[State]["PCut"] = PCut;
   DHFile[State]["NJet"] = NJet;

   DHFile[State]["P0T0"] = Parameter0[0];
   DHFile[State]["P0T1"] = Parameter0[1];
   DHFile[State]["P0T2"] = Parameter0[2];
   DHFile[State]["P0T3"] = Parameter0[3];
   DHFile[State]["P0T4"] = Parameter0[4];
   DHFile[State]["P0T5"] = Parameter0[5];
   
   DHFile[State]["P1T0"] = Parameter1[0];
   DHFile[State]["P1T1"] = Parameter1[1];
   DHFile[State]["P1T2"] = Parameter1[2];
   DHFile[State]["P1T3"] = Parameter1[3];
   DHFile[State]["P1T4"] = Parameter1[4];
   DHFile[State]["P1T5"] = Parameter1[5];
   DHFile[State]["P11"] = Parameter1[6];
   
   // DHFile[State]["P2T0"] = Parameter2[0];
   // DHFile[State]["P2T1"] = Parameter2[1];
   // DHFile[State]["P2T2"] = Parameter2[2];
   // DHFile[State]["P2T3"] = Parameter2[3];
   // DHFile[State]["P2T4"] = Parameter2[4];
   // DHFile[State]["P2T5"] = Parameter2[5];
   // DHFile[State]["P21"] = Parameter2[6];
   // DHFile[State]["P22"] = Parameter2[7];
   // 
   // DHFile[State]["P3T0"] = Parameter3[0];
   // DHFile[State]["P3T1"] = Parameter3[1];
   // DHFile[State]["P3T2"] = Parameter3[2];
   // DHFile[State]["P3T3"] = Parameter3[3];
   // DHFile[State]["P3T4"] = Parameter3[4];
   // DHFile[State]["P3T5"] = Parameter3[5];
   // DHFile[State]["P31"] = Parameter3[6];
   // DHFile[State]["P32"] = Parameter3[7];
   // DHFile[State]["P33"] = Parameter3[8];
   
   // DHFile[State]["P4T0"] = Parameter4[0];
   // DHFile[State]["P4T1"] = Parameter4[1];
   // DHFile[State]["P4T2"] = Parameter4[2];
   // DHFile[State]["P4T3"] = Parameter4[3];
   // DHFile[State]["P4T4"] = Parameter4[4];
   // DHFile[State]["P4T5"] = Parameter4[5];
   // DHFile[State]["P41"] = Parameter4[6];
   // DHFile[State]["P42"] = Parameter4[7];
   // DHFile[State]["P43"] = Parameter4[8];
   // DHFile[State]["P44"] = Parameter4[9];
  
   // DHFile[State]["P5T0"] = Parameter5[0];
   // DHFile[State]["P5T1"] = Parameter5[1];
   // DHFile[State]["P5T2"] = Parameter5[2];
   // DHFile[State]["P5T3"] = Parameter5[3];
   // DHFile[State]["P5T4"] = Parameter5[4];
   // DHFile[State]["P5T5"] = Parameter5[5];
   // DHFile[State]["P51"] = Parameter5[6];
   // DHFile[State]["P52"] = Parameter5[7];
   // DHFile[State]["P53"] = Parameter5[8];
   // DHFile[State]["P54"] = Parameter5[9];
   // DHFile[State]["P55"] = Parameter5[10];

   DHFile.SaveToFile(DHFileName);
   
   PdfFileHelper PdfFile(Validation);
   PdfFile.AddTextPage("Fit validation");

   vector<TH1D *> HMC, HData, HData0, HData1;

   for(int iB = 0; iB < 6; iB++)
   {
      HMC   .push_back(new TH1D(Form("HMCT%d", iB),    ";Mass;", 100, 0, 150));
      HData .push_back(new TH1D(Form("HDataT%d", iB),  ";Mass;", 100, 0, 150));
      HData0.push_back(new TH1D(Form("HData0T%d", iB), ";Mass;", 100, 0, 150));
      HData1.push_back(new TH1D(Form("HData1T%d", iB), ";Mass;", 100, 0, 150));
   }

   map<int, vector<double>> MMC = Events.MMC;
   map<int, vector<double>> MData = Events.GetMass(Events.EData, false, nullptr);
   Events.FunctionType = AllEvent::Const;
   map<int, vector<double>> MData0 = Events.GetMass(Events.EData, true, Parameter0);
   Events.FunctionType = AllEvent::Linear;
   map<int, vector<double>> MData1 = Events.GetMass(Events.EData, true, Parameter1);

   for(int iB = 0; iB < 6; iB++)
   {
      for(int i = 0; i < (int)MMC[iB].size(); i++)
         HMC[iB]->Fill(sqrt(MMC[iB][i]));
      for(int i = 0; i < (int)MData[iB].size(); i++)
         HData[iB]->Fill(sqrt(MData[iB][i]));
      for(int i = 0; i < (int)MData0[iB].size(); i++)
         HData0[iB]->Fill(sqrt(MData0[iB][i]));
      for(int i = 0; i < (int)MData1[iB].size(); i++)
         HData1[iB]->Fill(sqrt(MData1[iB][i]));
   }

   for(int iB = 0; iB < 6; iB++)
   {
      HMC[iB]->Scale(1 / HMC[iB]->Integral());
      HData[iB]->Scale(1 / HData[iB]->Integral());
      HData0[iB]->Scale(1 / HData0[iB]->Integral());
      HData1[iB]->Scale(1 / HData1[iB]->Integral());

      HMC[iB]->SetStats(0);
      HData[iB]->SetStats(0);
      HData0[iB]->SetStats(0);
      HData1[iB]->SetStats(0);

      HMC[iB]->SetMarkerStyle(20);
      HData[iB]->SetMarkerStyle(20);
      HData0[iB]->SetMarkerStyle(20);
      HData1[iB]->SetMarkerStyle(20);

      HMC[iB]->SetMarkerColor(kGreen);
      HData[iB]->SetMarkerColor(kRed);
      HData0[iB]->SetMarkerColor(kBlue - 7);
      HData1[iB]->SetMarkerColor(kBlue - 4);

      HMC[iB]->SetLineColor(kGreen);
      HData[iB]->SetLineColor(kRed);
      HData0[iB]->SetLineColor(kBlue - 7);
      HData1[iB]->SetLineColor(kBlue - 4);
   }

   TCanvas Canvas;

   for(auto &i : MMC)
      sort(i.second.begin(), i.second.end());

   TGraph GV;
   
   for(int iB = 0; iB < 6; iB++)
   {
      GV.SetPoint(0, sqrt(MMC[iB][MMC[iB].size()*0.1]), 1e-7);
      GV.SetPoint(1, sqrt(MMC[iB][MMC[iB].size()*0.1]), 100);
      GV.SetPoint(2, sqrt(MMC[iB][MMC[iB].size()*0.9]), 100);
      GV.SetPoint(3, sqrt(MMC[iB][MMC[iB].size()*0.9]), 1e-7);

      HMC[iB]->Draw();
      HData[iB]->Draw("same");
      HData0[iB]->Draw("same");
      HData1[iB]->Draw("same");
      GV.Draw("l");

      PdfFile.AddCanvas(Canvas);
      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);

      HData[iB]->Divide(HMC[iB]);
      HData0[iB]->Divide(HMC[iB]);
      HData1[iB]->Divide(HMC[iB]);

      HData0[iB]->GetYaxis()->SetTitle("Data / MC");
      HData0[iB]->SetMaximum(1.4);
      HData0[iB]->SetMinimum(0.6);

      HData0[iB]->Draw("");
      HData1[iB]->Draw("same");
      HData[iB]->Draw("same");
      GV.Draw("l");

      TGraph G;
      G.SetPoint(0, 0, 1);
      G.SetPoint(1, 10000, 1);
      G.Draw("l");

      Canvas.SetLogy(false);
      PdfFile.AddCanvas(Canvas);
   }

   for(int iB = 0; iB < 6; iB++)
   {
      delete HMC[iB];
      delete HData[iB];
      delete HData0[iB];
      delete HData1[iB];
   }
   
   int NBin = 12;
   double Bins[] = {0.15, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.85};
   TH1D H0("H0", ";#theta (#pi);JEC", NBin, Bins);
   TH1D H11("H11", ";#theta (#pi);JEC", NBin, Bins);
   TH1D H12("H12", ";#theta (#pi);JEC", NBin, Bins);
   H0.SetStats(0);
   Events.FunctionType = AllEvent::Const;
   for(int i = 1; i <= NBin; i++)
      H0.SetBinContent(i, Events.GetJEC(45, H0.GetBinCenter(i) * M_PI, Parameter0));
   Events.FunctionType = AllEvent::Linear;
   for(int i = 1; i <= NBin; i++)
   {
      H11.SetBinContent(i, Events.GetJEC(5, H11.GetBinCenter(i) * M_PI, Parameter1));
      H12.SetBinContent(i, Events.GetJEC(50, H12.GetBinCenter(i) * M_PI, Parameter1));
   }

   H0.SetLineColor(kRed);
   H11.SetLineColor(kBlue);
   H12.SetLineColor(kBlack);

   H0.SetLineWidth(2);
   H11.SetLineWidth(2);
   H12.SetLineWidth(2);

   H0.SetMaximum(1.05);
   H0.SetMinimum(0.95);

   TLegend Legend(0.5, 0.2, 0.8, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H0, "Constant", "l");
   Legend.AddEntry(&H11, "Linear, P = 5", "l");
   Legend.AddEntry(&H12, "Linear, P = 50", "l");

   H0.Draw();
   H11.Draw("same");
   H12.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



