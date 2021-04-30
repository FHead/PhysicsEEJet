#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLatex.h"
#include "TMatrixD.h"
#include "TGraphErrors.h"
#include "TGraph.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double CalculateSimpleChi2(TH1D *HMCTruth, TH1D *HUnfolded, int IgnoreBin = 0);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   string Method                 = CL.Get("Method", "UnfoldedBayes14");
   int IgnoreBin                 = CL.GetInt("IgnoreBin", 0);
   string Observable             = CL.Get("Observable", "");

   int BinCount = 0;
   if(InputFileNames.size() > 0)
   {
      TFile File(InputFileNames[0].c_str());
      TH1D *H = (TH1D *)File.Get("HMCTruth");
      BinCount = H->GetNbinsX();
      File.Close();
   }
   
   TH2D HPull("HPull", ";Bin Index;Pull", BinCount, 0, BinCount, 100, -5, 5);
   TH1D HPull1D("HPull1D", ";Pull;", 100, -5, 5);

   HPull.SetStats(0);
   HPull1D.SetStats(0);

   vector<vector<double>> Pulls(BinCount);
   vector<vector<double>> Vs(BinCount);

   bool FirstTime = true;
   TH1D HMCTruthCopy("HMCTruthCopy", "", BinCount, 0, BinCount);

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TH1D *HUnfolded = (TH1D *)File.Get(("H" + Method).c_str());
      TMatrixD Covariance = *((TMatrixD *)File.Get(("M" + Method).c_str()));

      TH1D *HTruth = (TH1D *)File.Get("HMCTruth");
      if(FirstTime == true)
      {
         for(int i = 1; i <= BinCount; i++)
            HMCTruthCopy.SetBinContent(i, HTruth->GetBinContent(i));
         FirstTime = false;
      }

      // double SimpleChi2 = CalculateSimpleChi2(HTruth, HUnfolded, IgnoreBin);
      // cout << SimpleChi2 << endl;

      for(int i = 1; i <= BinCount; i++)
      {
         double V1 = HUnfolded->GetBinContent(i);
         double V2 = HTruth->GetBinContent(i);
         double E = HUnfolded->GetBinError(i);
         HPull.Fill(i - 1, (V1 - V2) / E);

         Pulls[i-1].push_back((V1 - V2) / E);
         Vs[i-1].push_back(V1);

         if(i > IgnoreBin)
            HPull1D.Fill((V1 - V2) / E);
      }

      File.Close();
   }

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Statistics validation");

   PdfFile.AddPlot(HPull, "colz");
   PdfFile.AddPlot(HPull1D, "");

   double BlockLow = 0.0;
   double BlockHigh = 2.0;
   double BlockReturn = -1.0;

   TGraphErrors GMean, GSigma, GBlock, GIgnore;
   GBlock.SetPoint(0, 0, BlockLow);
   GIgnore.SetPoint(0, 0, BlockLow);
   for(int i = 0; i < BinCount; i++)
   {
      double Min = Vs[i][0], Max = Vs[i][0];
      for(double V : Vs[i])
      {
         if(Min > V)   Min = V;
         if(Max < V)   Max = V;
      }

      TH1D H("H", Form("Bin %d", i), 100, -5, 5);
      TH1D HV("HV", Form("Value: bin %d", i), 100, Min - (Max - Min) * 0.05, Max + (Max - Min) * 0.05);
      HV.GetXaxis()->SetNdivisions(303);

      double Sum0 = 0, Sum1 = 0, Sum2 = 0;
      for(double V : Pulls[i])
      {
         Sum0 = Sum0 + 1;
         Sum1 = Sum1 + V;
         Sum2 = Sum2 + V * V;
         H.Fill(V);
      }

      for(double V : Vs[i])
         HV.Fill(V);

      double Mean = Sum1 / Sum0;
      double RMS = sqrt((Sum2 - Sum1 * Sum1 / Sum0) / Sum0);

      TF1 F("F", "gaus", -5, 5);
      H.Fit(&F);

      // GMean.SetPoint(i, i + 0.5, F.GetParameter(1));
      // GMean.SetPointError(i, 0, F.GetParError(1));
      // GSigma.SetPoint(i, i + 0.5, F.GetParameter(2));
      // GSigma.SetPointError(i, 0, F.GetParError(2));
      
      GMean.SetPoint(i, i + 0.5, H.GetMean());
      GMean.SetPointError(i, 0, H.GetMeanError());
      GSigma.SetPoint(i, i + 0.5, H.GetRMS());
      GSigma.SetPointError(i, 0, H.GetRMSError());

      double NextPoint = BlockHigh;
      if(HMCTruthCopy.GetBinContent(i + 1) < 100)
         NextPoint = BlockHigh;
      else
         NextPoint = BlockLow;
      GBlock.SetPoint(GBlock.GetN(),     i, NextPoint);
      GBlock.SetPoint(GBlock.GetN(), i + 1, NextPoint);

      if(i >= IgnoreBin)
         NextPoint = BlockLow;
      else
         NextPoint = BlockHigh;
      GIgnore.SetPoint(GIgnore.GetN(),     i, NextPoint);
      GIgnore.SetPoint(GIgnore.GetN(), i + 1, NextPoint);

      PdfFile.AddPlot(HV);
      PdfFile.AddPlot(H);
   }

   GBlock.SetPoint(GBlock.GetN(), BinCount, BlockReturn);
   GBlock.SetPoint(GBlock.GetN(), 0, BlockReturn);

   GIgnore.SetPoint(GIgnore.GetN(), BinCount, BlockReturn);
   GIgnore.SetPoint(GIgnore.GetN(), 0, BlockReturn);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.045);
   Latex.SetNDC();
   Latex.SetTextAlign(12);

   TCanvas Canvas;
   TF1 FGaus("FGaus", "gaus", -5, 5);
   HPull1D.Fit(&FGaus);

   FGaus.SetLineColor(Colors[0]);
   HPull1D.SetLineColor(Colors[1]);
   HPull1D.SetLineWidth(3);
   HPull1D.SetMaximum(HPull1D.GetMaximum() * 1.4);

   HPull1D.Draw();

   Latex.DrawLatex(0.2, 0.82, Form("#mu = %.3f #pm %.3f", FGaus.GetParameter(1), FGaus.GetParError(1)));
   Latex.DrawLatex(0.2, 0.76, Form("#sigma = %.3f #pm %.3f", FGaus.GetParameter(2), FGaus.GetParError(2)));

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(GMean, "ap");
   PdfFile.AddPlot(GSigma, "ap");

   Canvas.cd();
   TH2D HWorld("HWorld", ";Bin Index;#sigma of pull distribution", BinCount, 0, BinCount, 100, 0.50, 1.50);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   GBlock.SetLineColor(Colors[5]);
   GBlock.SetFillColor(Colors[5]);
   GBlock.Draw("F");

   GIgnore.SetLineColor(Colors[4]);
   GIgnore.SetFillColor(Colors[4]);
   GIgnore.Draw("F");

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, BinCount, 1);
   GLine.Draw("l");
   
   HWorld.Draw("axis same");

   GSigma.SetLineColor(Colors[1]);
   GSigma.SetLineWidth(2);
   GSigma.SetMarkerStyle(20);
   GSigma.SetMarkerColor(Colors[1]);
   GSigma.SetMarkerSize(2);
   GSigma.Draw("p");

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.15, 0.94, Observable.c_str());

   Canvas.SaveAs(("Summary_" + OutputFileName).c_str());

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double CalculateSimpleChi2(TH1D *HMCTruth, TH1D *HUnfolded, int IgnoreBin)
{
   if(HMCTruth == nullptr || HUnfolded == nullptr)
      return 0;

   double Chi2 = 0;

   for(int i = IgnoreBin; i <= HMCTruth->GetNbinsX(); i++)
   {
      double V1 = HMCTruth->GetBinContent(i);
      double V2 = HUnfolded->GetBinContent(i);
      double E  = HUnfolded->GetBinError(i);

      Chi2 = Chi2 + (V1 - V2) * (V1 - V2) / E / E;
   }

   return Chi2;
}


