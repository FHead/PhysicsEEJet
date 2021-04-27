#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
#include "TGraphErrors.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 1000

struct Event;
struct BinResult;
int main(int argc, char *argv[]);
vector<BinResult> GetR(PdfFileHelper &PdfFile, string FileName);
pair<double, double> GetExtrapolatedR(PdfFileHelper &PdfFile, vector<Event> &E, double ThetaMin, double ThetaMax);
void DrawSummary(PdfFileHelper &PdfFile, vector<BinResult> &RData, vector<BinResult> &RMC);

struct Event
{
   FourVector Ref;
   FourVector Probe;
   double Alpha;
   bool operator <(const Event &other) const
   {
      if(Alpha < other.Alpha)   return true;
      if(Alpha > other.Alpha)   return false;
      if(Ref.InnerGetPT() < other.Ref.InnerGetPT())       return true;
      if(Ref.InnerGetPT() > other.Ref.InnerGetPT())       return false;
      if(Probe.InnerGetPT() < other.Probe.InnerGetPT())   return true;
      if(Probe.InnerGetPT() > other.Probe.InnerGetPT())   return false;
      return false;
   }
};

struct BinResult
{
   double R;
   double RError;
   double Min;
   double Max;
   bool operator <(const BinResult &other) const
   {
      if(Min < other.Min)      return true;
      if(Min > other.Min)      return false;
      if(Max < other.Max)      return true;
      if(Max > other.Max)      return false;
      if(R < other.R)          return true;
      if(R > other.R)          return true;
      if(RError < other.RError) return true;
      if(RError > other.RError) return true;
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string DataFileName = CL.Get("Data");
   string MCFileName   = CL.Get("MC");
   string PdfFileName  = CL.Get("Check", "CheckResidual.cpp");

   PdfFileHelper PdfFile(PdfFileName);
   PdfFile.AddTextPage("Residual check");
   
   vector<BinResult> RData = GetR(PdfFile, DataFileName);
   vector<BinResult> RMC = GetR(PdfFile, MCFileName);

   DrawSummary(PdfFile, RData, RMC);

   ofstream out("JECRelativeResidual.txt");

   out << "{1 JetTheta 1 JetPt [0]*([1]+[2]*x+[3]*x*x+[4]*x*x*x) RelativeResidual}" << endl;
   for(int i = 0; i < (int)RData.size(); i++)
      out << RData[i].Min << " " << RData[i].Max << " 7 10 44 " << RMC[i].R / RData[i].R << " 1 0 0 0" << endl;

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<BinResult> GetR(PdfFileHelper &PdfFile, string FileName)
{
   double RefThetaMin = 0.45 * M_PI;
   double RefThetaMax = 0.55 * M_PI;

   int ThetaBinCount = 10;
   double ThetaMin[] = {0.00, 0.20, 0.30, 0.35, 0.40, 0.55, 0.60, 0.65, 0.70, 0.80};
   double ThetaMax[] = {0.20, 0.30, 0.35, 0.40, 0.45, 0.60, 0.65, 0.70, 0.80, 1.00};
   vector<Event> ThetaEvents[10];

   for(int i = 0; i < ThetaBinCount; i++)
   {
      ThetaMin[i] = ThetaMin[i] * M_PI;
      ThetaMax[i] = ThetaMax[i] * M_PI;
   }

   int N;
   float JetPT[MAX], JetEta[MAX], JetTheta[MAX], JetPhi[MAX], JetM[MAX];

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");

   Tree->SetBranchAddress("N",        &N);
   Tree->SetBranchAddress("JetPT",    &JetPT);
   Tree->SetBranchAddress("JetEta",   &JetEta);
   Tree->SetBranchAddress("JetTheta", &JetTheta);
   Tree->SetBranchAddress("JetPhi",   &JetPhi);
   Tree->SetBranchAddress("JetM",     &JetM);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(N < 2)   // Mono-jet?!  Interesting, but not interesting here
         continue;

      bool J1InReference = false;
      bool J2InReference = false;
      if(JetTheta[0] > RefThetaMin && JetTheta[0] <= RefThetaMax)
         J1InReference = true;
      if(JetTheta[1] > RefThetaMin && JetTheta[1] <= RefThetaMax)
         J2InReference = true;

      if(J1InReference == false && J2InReference == false)   // we want a jet in reference region
         continue;
      if(J1InReference == true && J2InReference == true)   // Both are in reference region.  Not interesting
         continue;

      FourVector JRef, JProbe;
      JRef.SetPtEtaPhiMass(JetPT[0], JetEta[0], JetPhi[0]);
      JProbe.SetPtEtaPhiMass(JetPT[1], JetEta[1], JetPhi[1]);

      if(J2InReference == true)
         swap(JRef, JProbe);

      double Alpha = 0;
      if(N >= 3)
         Alpha = JetPT[2] / (JetPT[0] + JetPT[1]);

      Event E;
      E.Ref = JRef;
      E.Probe = JProbe;
      E.Alpha = Alpha;

      if(Alpha > 0.15)
         continue;
      if(JRef.GetPT() < 20)
         continue;

      for(int i = 0; i < ThetaBinCount; i++)
         if(ThetaMin[i] <= JProbe.GetTheta() && JProbe.GetTheta() < ThetaMax[i])
            ThetaEvents[i].push_back(E);
   }

   File.Close();

   vector<BinResult> Result;

   BinResult RefBin;
   RefBin.R = 1;
   RefBin.RError = 0;
   RefBin.Min = RefThetaMin;
   RefBin.Max = RefThetaMax;
   Result.push_back(RefBin);

   for(int iT = 0; iT < ThetaBinCount; iT++)
   {
      PdfFile.AddTextPage(FileName + Form(", theta bin %.2f#pi ~ %.2f#pi", ThetaMin[iT] / M_PI, ThetaMax[iT] / M_PI));

      pair<double, double> R = GetExtrapolatedR(PdfFile, ThetaEvents[iT], ThetaMin[iT] / M_PI, ThetaMax[iT] / M_PI);

      BinResult Bin;
      Bin.R = R.first;
      Bin.RError = R.second;
      Bin.Min = ThetaMin[iT];
      Bin.Max = ThetaMax[iT];

      Result.push_back(Bin);
   }

   sort(Result.begin(), Result.end());

   return Result;
}

pair<double, double> GetExtrapolatedR(PdfFileHelper &PdfFile, vector<Event> &E, double ThetaMin, double ThetaMax)
{
   int N = E.size();
   sort(E.begin(), E.end());

   TH1D HRefPT("HRefPT", ";Ref Jet PT;", 100, 0, 75);
   TH1D HProbePT("HProbePT", ";Probe Jet PT;", 100, 0, 75);
   TH1D HAlpha("HAlpha", ";alpha;", 100, 0, 1.0);
   TH1D HDPhi("HDPhi", ";#Delta#phi;", 100, -M_PI, M_PI);

   HRefPT.SetStats(0);
   HProbePT.SetStats(0);
   HAlpha.SetStats(0);
   HDPhi.SetStats(0);

   for(int i = 0; i < N; i++)
   {
      HRefPT.Fill(E[i].Ref.GetPT());
      HProbePT.Fill(E[i].Probe.GetPT());
      HAlpha.Fill(E[i].Alpha);
      HDPhi.Fill(GetDPhi(E[i].Ref, E[i].Probe));
   }

   PdfFile.AddPlot(HRefPT, "", true);
   PdfFile.AddPlot(HProbePT, "", true);
   PdfFile.AddPlot(HAlpha, "", true);
   PdfFile.AddPlot(HDPhi, "", true);

   int BinCount = 10;
   if(N < 1000)
      BinCount = N / 100;
   if(BinCount <= 2)
      BinCount = 1;

   TGraphErrors G;
   G.GetXaxis()->SetTitle("<#alpha>");
   G.GetYaxis()->SetTitle("<R>");
   G.GetYaxis()->SetNdivisions(305);
   G.GetXaxis()->SetNdivisions(305);

   G.SetMarkerSize(2);
   G.SetLineWidth(2);

   for(int iB = 0; iB < BinCount; iB++)
   {
      int Min = (N / BinCount) * iB;
      int Max = (N / BinCount) * (iB + 1);
      if(iB == BinCount - 1)
         Max = N;

      double SumR = 0, SumR2 = 0, SumAlpha = 0, SumAlpha2 = 0, Count = 0;
      for(int i = Min; i < Max; i++)
      {
         double R = E[i].Probe.GetPT() / E[i].Ref.GetPT();
         
         SumR2     = SumR2 + R * R;
         SumR      = SumR + R;
         SumAlpha2 = SumAlpha2 + E[i].Alpha * E[i].Alpha;
         SumAlpha  = SumAlpha + E[i].Alpha;
         Count     = Count + 1;
      }

      double MeanR = SumR / Count;
      double MeanAlpha = SumAlpha / Count;
      double RMSR = sqrt((SumR2 - SumR * SumR / Count) / Count) / sqrt(Count);
      double RMSAlpha = sqrt((SumAlpha2 - SumAlpha * SumAlpha / Count) / Count) / sqrt(Count);
      G.SetPoint(iB, MeanAlpha, MeanR);
      G.SetPointError(iB, RMSAlpha, RMSR);
   }

   TF1 F("F", "pol1");
   
   if(BinCount > 1)
      G.Fit(&F);
   
   G.GetXaxis()->SetRangeUser(0, 0.15);

   TCanvas Canvas;
   G.Draw("ap");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.06);
   Latex.SetTextAlign(12);
   Latex.SetNDC();
   if(F.GetParameter(1) >= 0)
      Latex.DrawLatex(0.20, 0.80, Form("%.2f#pi-%.2f#pi", ThetaMin, ThetaMax));
   else
      Latex.DrawLatex(0.20, 0.30, Form("%.2f#pi-%.2f#pi", ThetaMin, ThetaMax));

   PdfFile.AddCanvas(Canvas);

   double Result, Error;
   if(BinCount == 1)
   {
      double Dummy = 0;
      G.GetPoint(0, Dummy, Result);
      Error = G.GetErrorY(0);
   }
   else
   {
      Result = F.GetParameter(0);
      Error = F.GetParError(0);
   }

   return pair<double, double>(Result, Error);
}

void DrawSummary(PdfFileHelper &PdfFile, vector<BinResult> &RData, vector<BinResult> &RMC)
{
   TGraphErrors GData, GMC, GRatio;
   GData.GetXaxis()->SetTitle("#theta (#pi)");
   GData.GetYaxis()->SetTitle("R");
   GMC.GetXaxis()->SetTitle("#theta (#pi)");
   GMC.GetYaxis()->SetTitle("R");
   GRatio.GetXaxis()->SetTitle("#theta (#pi)");
   GRatio.GetYaxis()->SetTitle("Correction");

   GMC.SetLineColor(kRed);
   GMC.SetMarkerColor(kRed);

   for(int iT = 0; iT < (int)RData.size(); iT++)
   {
      GData.SetPoint(iT, (RData[iT].Min + RData[iT].Max) / 2 / M_PI, RData[iT].R);
      GData.SetPointError(iT, (RData[iT].Max - RData[iT].Min) / 2 / M_PI, RData[iT].RError);
   }
   for(int iT = 0; iT < (int)RMC.size(); iT++)
   {
      GMC.SetPoint(iT, (RMC[iT].Min + RMC[iT].Max) / 2 / M_PI, RMC[iT].R);
      GMC.SetPointError(iT, (RMC[iT].Max - RMC[iT].Min) / 2 / M_PI, RMC[iT].RError);
   }
   for(int iT = 0; iT < (int)RMC.size(); iT++)
   {
      double RelMC = RMC[iT].RError / RMC[iT].R;
      double RelData = RData[iT].RError / RData[iT].R;
      double Rel = sqrt(RelMC * RelMC + RelData * RelData);
      GRatio.SetPoint(iT, (RMC[iT].Min + RMC[iT].Max) / 2 / M_PI, RMC[iT].R / RData[iT].R);
      GRatio.SetPointError(iT, (RMC[iT].Max - RMC[iT].Min) / 2 / M_PI, RMC[iT].R / RData[iT].R * Rel);
   }

   PdfFile.AddTextPage("Summary Plot");

   GData.SetMarkerSize(2);
   GData.SetLineWidth(2);
   GMC.SetMarkerSize(2);
   GMC.SetLineWidth(2);
   GRatio.SetMarkerSize(2);
   GRatio.SetLineWidth(2);

   TCanvas Canvas;
   GData.Draw("ap");
   GMC.Draw("p");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.06);
   Latex.SetTextAlign(12);
   Latex.SetNDC();
   Latex.DrawLatex(0.40, 0.30, "#color[1]{Data} #color[2]{MC}");

   PdfFile.AddCanvas(Canvas);

   GRatio.Draw("ap");

   PdfFile.AddCanvas(Canvas);
}







