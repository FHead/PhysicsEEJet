#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   vector<string> FileNames1 = CL.GetStringVector("Files1", vector<string>{"MCVincia1LeadingDiJetE.root"});
   vector<string> FileNames2 = CL.GetStringVector("Files2", vector<string>{"MCVincia1TrueLeadingDiJetE.root"});
   vector<string> Labels = CL.GetStringVector("Labels", vector<string>{"P8 Shower 1"});

   int N = FileNames1.size();

   Assert(N == (int)FileNames2.size(), "File name mismatch");
   Assert(N == (int)Labels.size(), "Label mismatch");

   PdfFileHelper PdfFile(CL.Get("Output"));
   PdfFile.AddTextPage("Meowww");

   vector<TFile *> F1(N), F2(N);
   vector<TH1D *> H1(N), H2(N);

   for(int i = 0; i < N; i++)
   {
      F1[i] = TFile::Open(FileNames1[i].c_str());
      F2[i] = TFile::Open(FileNames2[i].c_str());
   }

   for(int i = 0; i < N; i++)
   {
      if(F1[i] != nullptr)
         H1[i] = (TH1D *)F1[i]->Get("HMCGen");
      else
         H1[i] = nullptr;
      
      if(F2[i] != nullptr)
         H2[i] = (TH1D *)F2[i]->Get("HMCGen");
      else
         H2[i] = nullptr;
   }

   for(int i = 0; i < N; i++)
   {
      PdfFile.AddTextPage(Labels[i]);

      H1[i]->SetLineColor(Colors[1]);
      H1[i]->SetLineWidth(2);
      H1[i]->SetMarkerColor(Colors[1]);
      H1[i]->SetMarkerSize(1.5);
      H1[i]->SetMarkerStyle(20);
      H2[i]->SetLineColor(Colors[2]);
      H2[i]->SetMarkerColor(Colors[2]);
      H2[i]->SetLineWidth(2);
      H2[i]->SetMarkerSize(1.5);
      H2[i]->SetMarkerStyle(20);

      H1[i]->SetStats(0);
      H2[i]->SetStats(0);

      TLegend Legend(0.2, 0.5, 0.5, 0.7);
      Legend.SetTextSize(0.035);
      Legend.SetTextFont(42);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(H1[i], "SumE Cut", "lp");
      Legend.AddEntry(H2[i], "Leading Dijet", "lp");

      if(H1[i]->Integral() > 0)
         H1[i]->Scale(1 / H1[i]->Integral());
      if(H2[i]->Integral() > 0)
         H2[i]->Scale(1 / H2[i]->Integral());

      TCanvas Canvas;
      H2[i]->Draw();
      H1[i]->Draw("same");
      Legend.Draw();
      PdfFile.AddCanvas(Canvas);

      H1[i]->Divide(H2[i]);

      H1[i]->Draw();

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTextPage("Summary plot");

   int NBin = H1[0]->GetNbinsX();

   TCanvas Canvas;
   TH2D HWorld("HWorld", ";Bin index;Ratio", NBin, 0, NBin, 100, 0, 2.5);
   HWorld.SetStats(0);
   HWorld.Draw();

   TLegend Legend(0.2, 0.4, 0.5, 0.85);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);

   for(int i = 0; i < N; i++)
   {
      H1[i]->SetMarkerColor(Colors[i]);
      H1[i]->SetLineColor(Colors[i]);

      H1[i]->Draw("same");

      Legend.AddEntry(H1[i], Labels[i].c_str(), "pl");
   }

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
   
   TH2D HWorld2("HWorld2", ";Bin index;Ratio", NBin, 0, NBin, 100, 0.5, 1.6);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   for(int i = 0; i < N; i++)
      H1[i]->Draw("same");

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   for(int i = 0; i < N; i++)
   {
      if(F1[i] != nullptr)   F1[i]->Close();
      if(F2[i] != nullptr)   F2[i]->Close();
   }

   return 0;
}



