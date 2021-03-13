#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AppendPlot(PdfFileHelper &PdfFile, vector<string> &Input, vector<string> &Label, string HistogramName);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileName = CL.GetStringVector("Input", vector<string>({}));
   vector<string> Label = CL.GetStringVector("Label", vector<string>({"A", "B", "C", "D", "E"}));
   string OutputFileName = CL.Get("Output", "AllPlots.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet fragmentation");

   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_20_25");
   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_25_30");
   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_30_35");
   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_35_37");
   AppendPlot(PdfFile, InputFileName, Label, "HJetXi_37_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD0ZG_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD0RG_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD0PF_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD1ZG_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD1RG_35_40");
   AppendPlot(PdfFile, InputFileName, Label, "HJetSD1PF_35_40");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}

void AppendPlot(PdfFileHelper &PdfFile, vector<string> &Input, vector<string> &Label, string HistogramName)
{
   int N = Input.size();

   vector<TFile *> Files;
   for(int i = 0; i < N; i++)
      Files.push_back(new TFile(Input[i].c_str()));

   TCanvas Canvas;

   vector<TH1D *> Histograms;
   for(int i = 0; i < N; i++)
   {
      if(Files[i] != nullptr)
         Histograms.push_back((TH1D *)Files[i]->Get(HistogramName.c_str()));
      else
         Histograms.push_back(nullptr);
   }

   TLegend Legend(0.4, 0.15, 0.7, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);

   int Colors[] = {kBlack, kRed, kBlue, kGreen, kCyan};
   for(int i = 0; i < N; i++)
   {
      Legend.AddEntry(Histograms[i], Label[i].c_str(), "pl");

      if(Histograms[i] == nullptr)
         continue;

      Histograms[i]->SetStats(0);
      Histograms[i]->SetLineColor(Colors[i]);
      Histograms[i]->SetMarkerColor(Colors[i]);
      Histograms[i]->Draw(i == 0 ? "" : "same");
   }

   Legend.Draw();
   PdfFile.AddCanvas(Canvas);

   if(Histograms[0] != nullptr)
   {
      TLegend LegendRatio(0.2, 0.8, 0.5, 0.6);
      LegendRatio.SetTextFont(42);
      LegendRatio.SetTextSize(0.035);
      LegendRatio.SetBorderSize(0);
      LegendRatio.SetFillStyle(0);
      
      TGraph G;
      G.SetPoint(0, 0, 1);
      G.SetPoint(1, 10000, 1);

      for(int i = 1; i < N; i++)
      {
         LegendRatio.AddEntry(Histograms[i], Label[i].c_str(), "pl");
         
         if(Histograms[i] == nullptr)
            continue;

         Histograms[i]->Divide(Histograms[0]);
         Histograms[i]->GetYaxis()->SetTitle("Ratio to pure pythia");
         Histograms[i]->SetMinimum(0.5);
         Histograms[i]->SetMaximum(1.5);

         Histograms[i]->Draw(i == 1 ? "" : "same");
      }

      G.Draw("l");

      LegendRatio.Draw();
      PdfFile.AddCanvas(Canvas);
   }

   for(int i = 0; i < N; i++)
      if(Files[i] != nullptr)
         delete Files[i];
}


