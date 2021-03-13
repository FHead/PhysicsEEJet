#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void FormatH1(TH1D *H);
void FormatH2(TH2D *H);
void MinMax(TH1D *H, int IgnoreBin = 0);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Unfolding plots");

   TFile InputFile(InputFileName.c_str());

   vector<string> H1Names{"HMCMeasured", "HMCTruth", "HInput", "HUnfoldedBayes1", "HUnfoldedBayes2",
      "HUnfoldedBayes3", "HUnfoldedBayes4", "HUnfoldedBayes6", "HUnfoldedBayes10", "HUnfodledBayes20",
      "HUnfoldedBayes30", "HUnfoldedBayes50", "HUnfoldedBayes100", "HUnfoldedBayes200"};
   vector<string> H2Names{"HMCResponse"};

   map<string, TH1D *> H1;
   map<string, TH2D *> H2;

   for(string Name : H1Names)
   {
      H1[Name] = (TH1D *)InputFile.Get(Name.c_str());
      FormatH1(H1[Name]);
   }
   for(string Name : H2Names)
   {
      H2[Name] = (TH2D *)InputFile.Get(Name.c_str());
      FormatH2(H2[Name]);
   }

   TCanvas Canvas;
   Canvas.SetGridx();
   Canvas.SetGridy();

   H2["HMCResponse"]->SetTitle("Response matrix");
   H2["HMCResponse"]->GetXaxis()->SetTitle("Reco Bin Index");
   H2["HMCResponse"]->GetYaxis()->SetTitle("Gen Bin Index");
   PdfFile.AddPlot(H2["HMCResponse"], "colz");
   PdfFile.AddPlot(H2["HMCResponse"], "colz", false, true);

   TLegend Legend1(0.45, 0.85, 0.8, 0.7);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetBorderSize(1);
   Legend1.AddEntry(H1["HMCMeasured"], "MC");
   Legend1.AddEntry(H1["HInput"], "Input reco");
   H1["HMCMeasured"]->SetLineColor(Colors[0]);
   H1["HMCMeasured"]->SetMarkerColor(Colors[0]);
   H1["HInput"]->SetLineColor(Colors[1]);
   H1["HInput"]->SetMarkerColor(Colors[1]);
   H1["HMCMeasured"]->SetTitle("Reco Distribution");
   H1["HMCMeasured"]->GetXaxis()->SetTitle("Bin index");
   H1["HMCMeasured"]->Draw();
   H1["HInput"]->Draw("same");
   Legend1.Draw();
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   H1["HMCMeasured"]->Draw();
   H1["HInput"]->Draw("same");
   Legend1.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);

   TLegend Legend2(0.45, 0.85, 0.8, 0.7);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetBorderSize(1);
   Legend2.AddEntry(H1["HMCTruth"], "MC truth");
   Legend2.AddEntry(H1["HUnfoldedBayes4"], "Unfolded (B-4)");
   H1["HMCTruth"]->SetLineColor(Colors[0]);
   H1["HMCTruth"]->SetMarkerColor(Colors[0]);
   H1["HUnfoldedBayes4"]->SetLineColor(Colors[1]);
   H1["HUnfoldedBayes4"]->SetMarkerColor(Colors[1]);
   H1["HMCTruth"]->SetTitle("Unfolded distribution");
   H1["HMCTruth"]->GetXaxis()->SetTitle("Bin index");
   H1["HMCTruth"]->Scale(H1["HUnfoldedBayes4"]->Integral() / H1["HMCTruth"]->Integral());
   H1["HMCTruth"]->Draw();
   H1["HUnfoldedBayes4"]->Draw("same");
   Legend2.Draw();
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   H1["HMCTruth"]->Draw();
   H1["HUnfoldedBayes4"]->Draw("same");
   Legend2.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);

   TH1D *HRatioBayes4 = (TH1D *)H1["HUnfoldedBayes4"]->Clone("HRatioBayes4");
   HRatioBayes4->Divide(H1["HMCTruth"]);
   HRatioBayes4->Draw();
   HRatioBayes4->SetTitle("");
   HRatioBayes4->GetYaxis()->SetTitle("Unfolded (B-4) / MCTruth");
   MinMax(HRatioBayes4, 1);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TLegend Legend3(0.3, 0.85, 0.65, 0.6);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetBorderSize(1);
   Legend3.AddEntry(H1["HUnfoldedBayes1"], "Unfolded (B-1)");
   Legend3.AddEntry(H1["HUnfoldedBayes2"], "Unfolded (B-2)");
   Legend3.AddEntry(H1["HUnfoldedBayes4"], "Unfolded (B-4)");
   Legend3.AddEntry(H1["HUnfoldedBayes10"], "Unfolded (B-10)");
   Legend3.AddEntry(H1["HUnfoldedBayes100"], "Unfolded (B-100)");
   H1["HUnfoldedBayes1"]->SetLineColor(Colors[0]);
   H1["HUnfoldedBayes1"]->SetMarkerColor(Colors[0]);
   H1["HUnfoldedBayes2"]->SetLineColor(Colors[2]);
   H1["HUnfoldedBayes2"]->SetMarkerColor(Colors[2]);
   H1["HUnfoldedBayes4"]->SetLineColor(Colors[1]);
   H1["HUnfoldedBayes4"]->SetMarkerColor(Colors[1]);
   H1["HUnfoldedBayes10"]->SetLineColor(Colors[3]);
   H1["HUnfoldedBayes10"]->SetMarkerColor(Colors[3]);
   H1["HUnfoldedBayes100"]->SetLineColor(Colors[4]);
   H1["HUnfoldedBayes100"]->SetMarkerColor(Colors[4]);
   H1["HUnfoldedBayes1"]->SetTitle("Unfolded distribution");
   H1["HUnfoldedBayes1"]->GetXaxis()->SetTitle("Bin Index");
   H1["HUnfoldedBayes1"]->Draw();
   H1["HUnfoldedBayes2"]->Draw("same");
   H1["HUnfoldedBayes4"]->Draw("same");
   H1["HUnfoldedBayes10"]->Draw("same");
   H1["HUnfoldedBayes100"]->Draw("same");
   Legend3.Draw();
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   H1["HUnfoldedBayes1"]->Draw();
   H1["HUnfoldedBayes2"]->Draw("same");
   H1["HUnfoldedBayes4"]->Draw("same");
   H1["HUnfoldedBayes10"]->Draw("same");
   H1["HUnfoldedBayes100"]->Draw("same");
   Legend3.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   
   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void FormatH1(TH1D *H)
{
   if(H == nullptr)
      return;

   H->SetMarkerStyle(20);
   H->SetLineWidth(2);
   H->SetStats(0);
}

void FormatH2(TH2D *H)
{
   if(H == nullptr)
      return;

   H->Fill(0.0, 0.0, 0.0);
   H->SetStats(0);
}

void MinMax(TH1D *H, int IgnoreBin)
{
   double Min = 999;
   double Max = -999;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      if(i <= IgnoreBin)
         continue;
      double X = H->GetBinContent(i);
      double E = H->GetBinError(i);
      if(X == 0 && E == 0)
         continue;
      if(Min > X - E)   Min = X - E;
      if(Max < X + E)   Max = X + E;
   }

   double D = Max - Min;
   Min = Min - D * 0.1;
   Max = Max + D * 0.1;

   H->SetMinimum(Min);
   H->SetMaximum(Max);
}



