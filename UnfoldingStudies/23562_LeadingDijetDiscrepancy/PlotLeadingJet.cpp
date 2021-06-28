#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string MCFile   = CL.Get("MC", "MC.root");
   string DataFile = CL.Get("Data", "Data.root");
   string Output   = CL.Get("Output", "Meow.pdf");
   
   TFile FMC(MCFile.c_str());
   TFile FData(DataFile.c_str());

   TTree *TMC = (TTree *)FMC.Get("UnfoldingTree");
   TTree *TData = (TTree *)FData.Get("UnfoldingTree");

   TH2D HMC2D("HMC2D", "MC;E1;E2", 60, 0, 60, 60, 0, 60);
   TH2D HData2D("HData2D", "Data;E1;E2", 60, 0, 60, 60, 0, 60);
   
   TH1D HMCJ1("HMCJ1", ";J1", 60, 0, 60);
   TH1D HMCJ2("HMCJ2", ";J2", 60, 0, 60);
   TH1D HMCJ12("HMCJ12", ";J+J", 60, 0, 100);
   TH1D HDataJ1("HDataJ1", ";J1", 60, 0, 60);
   TH1D HDataJ2("HDataJ2", ";J2", 60, 0, 60);
   TH1D HDataJ12("HDataJ12", ";J+J", 60, 0, 100);

   HMC2D.SetStats(0);
   HData2D.SetStats(0);
   HMCJ1.SetStats(0);
   HMCJ2.SetStats(0);
   HMCJ12.SetStats(0);
   HDataJ1.SetStats(0);
   HDataJ2.SetStats(0);
   HDataJ12.SetStats(0);

   HMCJ1.SetLineColor(Colors[0]);
   HMCJ2.SetLineColor(Colors[0]);
   HMCJ12.SetLineColor(Colors[0]);
   HMCJ1.SetMarkerColor(Colors[0]);
   HMCJ2.SetMarkerColor(Colors[0]);
   HMCJ12.SetMarkerColor(Colors[0]);
   HDataJ1.SetLineColor(Colors[1]);
   HDataJ2.SetLineColor(Colors[1]);
   HDataJ12.SetLineColor(Colors[1]);
   HDataJ1.SetMarkerColor(Colors[1]);
   HDataJ2.SetMarkerColor(Colors[1]);
   HDataJ12.SetMarkerColor(Colors[1]);

   TMC->Draw("RecoJetE[1]:RecoJetE[0]>>HMC2D");
   TData->Draw("RecoJetE[1]:RecoJetE[0]>>HData2D");
   
   TMC->Draw("RecoJetE[0]>>HMCJ1");
   TMC->Draw("RecoJetE[1]>>HMCJ2");
   TMC->Draw("RecoJetE[0]+RecoJetE[1]>>HMCJ12");
   TData->Draw("RecoJetE[0]>>HDataJ1");
   TData->Draw("RecoJetE[1]>>HDataJ2");
   TData->Draw("RecoJetE[0]+RecoJetE[1]>>HDataJ12");

   HMC2D.Scale(1 / HMC2D.Integral());
   HData2D.Scale(1 / HData2D.Integral());

   HMCJ1.Scale(1 / HMCJ1.Integral());
   HMCJ2.Scale(1 / HMCJ2.Integral());
   HMCJ12.Scale(1 / HMCJ12.Integral());
   HDataJ1.Scale(1 / HDataJ1.Integral());
   HDataJ2.Scale(1 / HDataJ2.Integral());
   HDataJ12.Scale(1 / HDataJ12.Integral());

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Meow");

   PdfFile.AddPlot(HMC2D, "colz", false, true);
   PdfFile.AddPlot(HData2D, "colz", false, true);

   TLegend Legend(0.2, 0.6, 0.5, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HMCJ1, "MC", "pl");
   Legend.AddEntry(&HDataJ1, "Data", "pl");

   TCanvas Canvas;
   Canvas.SetLogy();

   HMCJ1.Draw();
   HDataJ1.Draw("same");
   Legend.Draw();
   PdfFile.AddCanvas(Canvas);

   HMCJ2.Draw();
   HDataJ2.Draw("same");
   Legend.Draw();
   PdfFile.AddCanvas(Canvas);

   HMCJ12.Draw();
   HDataJ12.Draw("same");
   Legend.Draw();
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FData.Close();
   FMC.Close();

   return 0;
}


