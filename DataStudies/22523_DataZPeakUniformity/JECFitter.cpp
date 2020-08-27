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
   vector<double> MMC;
   double PCut;
   int NJet;
   enum {Const, Linear, Quadratic, Cubic, Quartic, Cintic} FunctionType;
public:
   AllEvent();
   AllEvent(string FileNameMC, string FileNameData, double MinimumP = 5, int MaximumN = 3);
   void Initialize(string FileNameMC, string FileNameData, double MinimumP = 5, int MaximumN = 3);
   void ReadFile(vector<Event> &E, string FileName);
   vector<double> GetMass(const vector<Event> &E, bool ApplyJEC, const double *Parameters) const;
   double GetJEC(double P, double Theta, const double *Parameters) const;
   double Likelihood(const double *Parameters);
   const double *DoFit();
};

AllEvent::AllEvent()
{
}

AllEvent::AllEvent(string FileNameMC, string FileNameData, double MinimumP, int MaximumN)
{
   Initialize(FileNameMC, FileNameData, MinimumP, MaximumN);
}

void AllEvent::Initialize(string FileNameMC, string FileNameData, double MinimumP, int MaximumN)
{
   PCut = MinimumP;
   NJet = MaximumN;

   ReadFile(EMC, FileNameMC);
   ReadFile(EData, FileNameData);

   MMC = GetMass(EMC, false, nullptr);
   sort(MMC.begin(), MMC.end());
}

void AllEvent::ReadFile(vector<Event> &E, string FileName)
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

   int EntryCount = Tree->GetEntries();
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

vector<double> AllEvent::GetMass(const vector<Event> &E, bool ApplyJEC, const double *Parameters) const
{
   vector<double> Result;
   Result.clear();

   for(int i = 0; i < (int)E.size(); i++)
   {
      double SumE = 0, SumX = 0, SumY = 0, SumZ = 0;
      int JetCount = 0;
      for(int j = 0; j < E[i].N; j++)
      {
         double P = sqrt(E[i].PX[j] * E[i].PX[j] + E[i].PY[j] * E[i].PY[j] + E[i].PZ[j] * E[i].PZ[j]);
         double Theta = acos(E[i].PZ[j] / P);
         double JEC = (ApplyJEC ? GetJEC(P, Theta, Parameters) : 1);
         if((E[i].PX[j] * E[i].PX[j] + E[i].PY[j] * E[i].PY[j]) * JEC < PCut)
            continue;
         SumE = SumE + E[i].E[j]  * JEC;
         SumX = SumX + E[i].PX[j] * JEC;
         SumY = SumY + E[i].PY[j] * JEC;
         SumZ = SumZ + E[i].PZ[j] * JEC;
         JetCount = JetCount + 1;
      }
      double M2 = SumE * SumE - SumX * SumX - SumY * SumY - SumZ * SumZ;
      if(M2 < MINMASS * MINMASS || M2 > MAXMASS * MAXMASS)
         continue;
      if(JetCount > NJet)
         continue;
      Result.push_back(M2);
   }

   return Result;
}

double AllEvent::GetJEC(double P, double Theta, const double *Parameters) const
{
   if(Parameters == nullptr)
      return 1;

   // Clipping
   if(P < PCut)   P = PCut;

   double Overall = 1;
   if(Theta < 0.3 * M_PI)
      Overall = Parameters[0];
   else if(Theta < 0.4 * M_PI)
      Overall = Parameters[1];
   else if(Theta < 0.5 * M_PI)
      Overall = Parameters[2];
   else if(Theta < 0.6 * M_PI)
      Overall = Parameters[3];
   else if(Theta < 0.7 * M_PI)
      Overall = Parameters[4];
   else
      Overall = Parameters[5];

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

   vector<double> MData = GetMass(EData, true, Parameters);
   sort(MData.begin(), MData.end());

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
   for(int i = 5; i < 45; i++)
   {
      double SumMC = 0, SumData = 0;
      int CountMC = MMC.size() / N, CountData = MData.size() / N;
      for(int j = CountMC * i; j < CountMC * (i + 1); j++)
         SumMC = SumMC + sqrt(MMC[j]);
      for(int j = CountData * i; j < CountData * (i + 1); j++)
         SumData = SumData + sqrt(MData[j]);
      double Delta = SumMC / CountMC - SumData / CountData;
      LL = LL + Delta * Delta / (MAXMASS - MINMASS);
      // cout << "   " << i << " " << SumMC / CountMC << " " << SumData / CountData << endl;
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

   AllEvent Events(FileNameMC, FileNameData, PCut, NJet);
   
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
   // 
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
   // 
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

   TH1D HMC("HMC", ";Mass;", 100, 0, 150);
   TH1D HData("HData", ";Mass;", 100, 0, 150);
   TH1D HData0("HData0", ";Mass;", 100, 0, 150);
   TH1D HData1("HData1", ";Mass;", 100, 0, 150);
   TH1D HData2("HData2", ";Mass;", 100, 0, 150);
   TH1D HData3("HData3", ";Mass;", 100, 0, 150);
   TH1D HData4("HData4", ";Mass;", 100, 0, 150);
   TH1D HData5("HData5", ";Mass;", 100, 0, 150);

   vector<double> MMC = Events.MMC;
   vector<double> MData = Events.GetMass(Events.EData, false, nullptr);
   Events.FunctionType = AllEvent::Const;
   vector<double> MData0 = Events.GetMass(Events.EData, true, Parameter0);
   Events.FunctionType = AllEvent::Linear;
   vector<double> MData1 = Events.GetMass(Events.EData, true, Parameter1);
   // Events.FunctionType = AllEvent::Quadratic;
   // vector<double> MData2 = Events.GetMass(Events.EData, true, Parameter2);
   // Events.FunctionType = AllEvent::Cubic;
   // vector<double> MData3 = Events.GetMass(Events.EData, true, Parameter3);
   // Events.FunctionType = AllEvent::Quartic;
   // vector<double> MData4 = Events.GetMass(Events.EData, true, Parameter4);
   // Events.FunctionType = AllEvent::Cintic;
   // vector<double> MData5 = Events.GetMass(Events.EData, true, Parameter5);

   for(int i = 0; i < (int)MMC.size(); i++)
      HMC.Fill(sqrt(MMC[i]));
   for(int i = 0; i < (int)MData.size(); i++)
      HData.Fill(sqrt(MData[i]));
   for(int i = 0; i < (int)MData0.size(); i++)
      HData0.Fill(sqrt(MData0[i]));
   for(int i = 0; i < (int)MData1.size(); i++)
      HData1.Fill(sqrt(MData1[i]));
   // for(int i = 0; i < (int)MData2.size(); i++)
   //    HData2.Fill(sqrt(MData2[i]));
   // for(int i = 0; i < (int)MData3.size(); i++)
   //    HData3.Fill(sqrt(MData3[i]));
   // for(int i = 0; i < (int)MData4.size(); i++)
   //    HData4.Fill(sqrt(MData4[i]));
   // for(int i = 0; i < (int)MData5.size(); i++)
   //    HData5.Fill(sqrt(MData5[i]));

   HMC.Scale(1 / HMC.Integral());
   HData.Scale(1 / HData.Integral());
   HData0.Scale(1 / HData0.Integral());
   HData1.Scale(1 / HData1.Integral());
   // HData2.Scale(1 / HData2.Integral());
   // HData3.Scale(1 / HData3.Integral());
   // HData4.Scale(1 / HData4.Integral());
   // HData5.Scale(1 / HData5.Integral());

   HMC.SetStats(0);
   HData.SetStats(0);
   HData0.SetStats(0);
   HData1.SetStats(0);
   // HData2.SetStats(0);
   // HData3.SetStats(0);
   // HData4.SetStats(0);
   // HData5.SetStats(0);

   HMC.SetMarkerStyle(20);
   HData.SetMarkerStyle(20);
   HData0.SetMarkerStyle(20);
   HData1.SetMarkerStyle(20);
   // HData2.SetMarkerStyle(20);
   // HData3.SetMarkerStyle(20);
   // HData4.SetMarkerStyle(20);
   // HData5.SetMarkerStyle(20);
   
   HMC.SetMarkerColor(kGreen);
   HData.SetMarkerColor(kRed);
   HData0.SetMarkerColor(kBlue - 7);
   HData1.SetMarkerColor(kBlue - 4);
   // HData2.SetMarkerColor(kBlue);
   // HData3.SetMarkerColor(kBlue + 2);
   // HData4.SetMarkerColor(kBlue + 4);
   // HData5.SetMarkerColor(kBlack);
   
   HMC.SetLineColor(kGreen);
   HData.SetLineColor(kRed);
   HData0.SetLineColor(kBlue - 7);
   HData1.SetLineColor(kBlue - 4);
   // HData2.SetLineColor(kBlue);
   // HData3.SetLineColor(kBlue + 2);
   // HData4.SetLineColor(kBlue + 4);
   // HData5.SetLineColor(kBlack);

   TCanvas Canvas;

   sort(MMC.begin(), MMC.end());

   TGraph GV;
   GV.SetPoint(0, sqrt(MMC[MMC.size()*0.1]), 1e-7);
   GV.SetPoint(1, sqrt(MMC[MMC.size()*0.1]), 100);
   GV.SetPoint(2, sqrt(MMC[MMC.size()*0.9]), 100);
   GV.SetPoint(3, sqrt(MMC[MMC.size()*0.9]), 1e-7);

   HMC.Draw();
   HData.Draw("same");
   HData0.Draw("same");
   HData1.Draw("same");
   // HData2.Draw("same");
   // HData3.Draw("same");
   // HData4.Draw("same");
   GV.Draw("l");

   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   HData.Divide(&HMC);
   HData0.Divide(&HMC);
   HData1.Divide(&HMC);
   // HData2.Divide(&HMC);
   // HData3.Divide(&HMC);
   // HData4.Divide(&HMC);
   // HData5.Divide(&HMC);

   HData0.GetYaxis()->SetTitle("Data / MC");
   HData0.SetMaximum(1.4);
   HData0.SetMinimum(0.6);

   HData0.Draw("");
   HData1.Draw("same");
   // HData2.Draw("same");
   // HData3.Draw("same");
   // HData4.Draw("same");
   // HData5.Draw("same");
   HData.Draw("same");
   GV.Draw("l");

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 10000, 1);
   G.Draw("l");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH1D H0("H0", ";#theta (#pi);JEC", 6, 0.2, 0.8);
   TH1D H11("H11", ";#theta (#pi);JEC", 6, 0.2, 0.8);
   TH1D H12("H12", ";#theta (#pi);JEC", 6, 0.2, 0.8);
   H0.SetStats(0);
   H0.SetBinContent(1, Parameter0[0]);
   H0.SetBinContent(2, Parameter0[1]);
   H0.SetBinContent(3, Parameter0[2]);
   H0.SetBinContent(4, Parameter0[3]);
   H0.SetBinContent(5, Parameter0[4]);
   H0.SetBinContent(6, Parameter0[5]);
   H11.SetBinContent(1, Parameter1[0] * (1 + Parameter1[6] * 5));
   H11.SetBinContent(2, Parameter1[1] * (1 + Parameter1[6] * 5));
   H11.SetBinContent(3, Parameter1[2] * (1 + Parameter1[6] * 5));
   H11.SetBinContent(4, Parameter1[3] * (1 + Parameter1[6] * 5));
   H11.SetBinContent(5, Parameter1[4] * (1 + Parameter1[6] * 5));
   H11.SetBinContent(6, Parameter1[5] * (1 + Parameter1[6] * 5));
   H12.SetBinContent(1, Parameter1[0] * (1 + Parameter1[6] * 50));
   H12.SetBinContent(2, Parameter1[1] * (1 + Parameter1[6] * 50));
   H12.SetBinContent(3, Parameter1[2] * (1 + Parameter1[6] * 50));
   H12.SetBinContent(4, Parameter1[3] * (1 + Parameter1[6] * 50));
   H12.SetBinContent(5, Parameter1[4] * (1 + Parameter1[6] * 50));
   H12.SetBinContent(6, Parameter1[5] * (1 + Parameter1[6] * 50));

   H0.SetLineColor(kRed);
   H11.SetLineColor(kBlue);
   H12.SetLineColor(kBlack);
   
   H0.SetLineWidth(2);
   H11.SetLineWidth(2);
   H12.SetLineWidth(2);

   H0.SetMaximum(1.1);
   H0.SetMinimum(0.9);

   TLegend Legend(0.5, 0.2, 0.8, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H0, "Constant", "l");
   Legend.AddEntry(&H11, "Linear, P = 5", "l");
   Legend.AddEntry(&H12, "Linear, P = 10", "l");

   H0.Draw();
   H11.Draw("same");
   H12.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



