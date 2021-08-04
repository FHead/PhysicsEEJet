#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThumbStyle();

   double Max = 1200;
   double Min = 0;
   int Bin = 100;

   TH1D HData("HData", ";Total momentum (GeV);a.u.", Bin, Min, Max);
   TH1D HData1994("HData1994", ";Total momentum (GeV);a.u.", Bin, Min, Max);
   TH1D HMC("HMC", ";Total momentum (GeV);a.u.", Bin, Min, Max);

   HData.Sumw2();
   HData1994.Sumw2();
   HMC.Sumw2();

   TChain DataChain("Data", "Data");
   DataChain.AddFile("DataSamples/LEP1Data1992_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.AddFile("DataSamples/LEP1Data1993_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.AddFile("DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.AddFile("DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.AddFile("DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.AddFile("DataSamples/LEP1Data1995_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain.Draw("Sum$(pmag)>>HData", "");

   TChain DataChain1994("Data", "Data");
   DataChain1994.AddFile("DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain1994.AddFile("DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain1994.AddFile("DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root", TTree::kMaxEntries, "t");
   DataChain1994.Draw("Sum$(pmag)>>HData1994", "");

   TChain MCChain;
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-001.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-002.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-003.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-004.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-005.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-006.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-007.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-008.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-009.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-010.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-011.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-012.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-013.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-014.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-015.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-016.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-017.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-018.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-019.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-020.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-021.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-022.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-023.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-024.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-025.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-026.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-027.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-028.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-029.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-030.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-031.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-032.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-033.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-034.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-035.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-036.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-037.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-038.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-039.root", TTree::kMaxEntries, "t");
   MCChain.AddFile("MCSamples/LEP1MC1994_recons_aftercut-040.root", TTree::kMaxEntries, "t");
   MCChain.Draw("Sum$(pmag)>>HMC", "", "same");

   double BinWidth = (Max - Min) / Bin;
   HData.Scale(1 / HData.Integral() / BinWidth);
   HData1994.Scale(1 / HData1994.Integral() / BinWidth);
   HMC.Scale(1 / HMC.Integral() / BinWidth);

   HData.SetStats(0);
   HData.SetMarkerColor(Colors[0]);
   HData.SetMarkerSize(2);
   HData.SetLineColor(Colors[0]);
   HData.SetLineWidth(2);
   
   HData1994.SetStats(0);
   HData1994.SetMarkerColor(Colors[5]);
   HData1994.SetMarkerSize(2);
   HData1994.SetLineColor(Colors[5]);
   HData1994.SetLineWidth(2);

   HMC.SetStats(0);
   HMC.SetMarkerColor(Colors[1]);
   HMC.SetLineColor(Colors[1]);
   HMC.SetLineWidth(2);

   TLegend Legend(0.35, 0.8, 0.65, 0.55);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HData, "Data (1992-1995)", "pl");
   Legend.AddEntry(&HData1994, "Data (1994)", "pl");
   Legend.AddEntry(&HMC, "Simulation", "l");

   TCanvas Canvas;

   HData.Draw();
   HData1994.Draw("same");
   HMC.Draw("hist same");
   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetNDC();
   Latex.SetTextAlign(11);

   Latex.DrawLatex(0.15, 0.91, "ALEPH Archived e^{+}e^{-} Data");

   Canvas.SetLogy();
   Canvas.SaveAs("TotalMomentum.pdf");

   return 0;
}
