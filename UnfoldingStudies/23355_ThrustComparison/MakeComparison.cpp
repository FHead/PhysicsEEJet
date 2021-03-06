#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 10000, 1);

   TFile FA("HEPData-ins636645-v1-Table54.root");
   TH1D *HA = (TH1D *)FA.Get("Table 54/Hist1D_y1");
   HA->SetStats(0);

   HA->GetXaxis()->SetTitle("Thrust");
   HA->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d #sigma}{d Thrust}");
   HA->SetTitle("Thrust reproduction");

   for(int i = 1; i <= HA->GetNbinsX(); i++)
      HA->SetBinError(i, 0);

   TFile FT("ThrustCorrection.root");
   TH1D *HR = (TH1D *)FT.Get("HR");

   TFile FB("Input/DataThrustUniform.root");
   TH1D *HB1 = (TH1D *)FB.Get("HUnfoldedSVD");
   TH1D *HB2 = (TH1D *)FB.Get("HInput");

   TH1D H1("H1", "", 42, 0.58, 1.00);
   TH1D H2("H2", "", 42, 0.58, 1.00);
   H1.Sumw2();
   H2.Sumw2();

   for(int i = 1; i <= 42; i++)
   {
      H1.SetBinContent(i, HB1->GetBinContent(i));
      H1.SetBinError(i, HB1->GetBinError(i));
      H2.SetBinContent(i, HB2->GetBinContent(i));
      H2.SetBinError(i, HB2->GetBinError(i));
   }

   H1.SetMarkerStyle(20);
   H2.SetMarkerStyle(20);

   H1.SetLineWidth(2);
   H1.SetLineColor(Colors[0]);
   H1.SetMarkerColor(Colors[0]);
   H2.SetLineWidth(2);
   H2.SetLineColor(Colors[1]);
   H2.SetMarkerColor(Colors[1]);

   H1.Scale(1 / H1.Integral() / 0.01);
   H2.Scale(1 / H2.Integral() / 0.01);

   PdfFileHelper PdfFile("ThrustReproductionMeow.pdf");
   PdfFile.AddTextPage("Thrust reproduction");

   TCanvas Canvas;

   HA->SetLineWidth(2);
   HA->SetLineColor(Colors[4]);

   HA->Draw("hist");
   H1.Draw("same");
   H2.Draw("same");

   TLegend Legend1(0.5, 0.2, 0.8, 0.2 + 0.04 * 3);
   Legend1.SetTextSize(0.035);
   Legend1.SetTextFont(42);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(HA, "Published", "l");
   Legend1.AddEntry(&H1, "Unfolded", "p");
   Legend1.AddEntry(&H2, "Input", "p");
   Legend1.Draw();

   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   
   H1.GetXaxis()->SetTitle("Thrust");
   H1.GetYaxis()->SetTitle("Ratio to Published");

   H1.Divide(HA);
   H2.Divide(HA);

   HR->SetLineWidth(2);
   HR->SetLineColor(Colors[4]);
   HR->SetMarkerColor(Colors[4]);

   H1.SetStats(0);
   
   TLegend Legend2(0.5, 0.65, 0.8, 0.65 + 0.04 * 3);
   Legend2.SetTextSize(0.035);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&H1, "Unfolded", "lp");
   Legend2.AddEntry(&H2, "Input", "lp");
   Legend2.AddEntry(HR, "Correction", "lp");

   H1.SetMinimum(0.0);
   H1.SetMaximum(2.5);

   H1.Draw();
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   HR->Draw("same");
   HR->Draw("hist same");
   GLine.Draw("l");
   
   Legend2.Draw();

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   H1.SetMinimum(0.5);
   H1.SetMaximum(1.5);
   PdfFile.AddCanvas(Canvas);

   TFile FC("Perfect/PerfectHEPDataThrustUniform.root");

   TH1D *HC = (TH1D *)FC.Get("HDataReco");

   HC->SetLineWidth(2);
   HC->SetLineColor(Colors[2]);
   HB2->SetLineWidth(2);
   HB2->SetLineColor(Colors[3]);
   HB2->SetMarkerStyle(20);
   HB2->SetMarkerColor(Colors[3]);

   HC->SetStats(0);

   HC->Scale(1 / HC->Integral() / 0.01);
   HB2->Scale(1 / HB2->Integral() / 0.01);

   HC->Draw();
   HB2->Draw("same");

   TLegend Legend3(0.2, 0.7, 0.5, 0.7 + 0.04 * 2);
   Legend3.SetTextSize(0.035);
   Legend3.SetTextFont(42);
   Legend3.SetBorderSize(0);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(HC, "Folded published", "l");
   Legend3.AddEntry(HB2, "Input", "l");
   Legend3.Draw();

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   HB2->SetMinimum(0.0);
   HB2->SetMaximum(2.5);
   
   HB2->Divide(HC);

   HB2->SetStats(0);
   HB2->GetYaxis()->SetTitle("Sample / Folded published");

   HB2->Draw();
   GLine.Draw("l");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FC.Close();
   FB.Close();
   FA.Close();

   return 0;
}


