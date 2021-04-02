#include <iostream>
#include <vector>
using namespace std;

#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   vector<string> Labels = CL.GetStringVector("Labels");
   vector<string> Variations = CL.GetStringVector("Variations");

   Assert(Variations.size() > 0, "No variations selected");
   Assert(Labels.size() == Variations.size(), "Variation and labeling not consistent");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Systematics");

   TGraph GLine;
   GLine.SetPoint(0, -1000, 1);
   GLine.SetPoint(1, +1000, 1);

   TFile File(InputFileName.c_str());

   vector<TH1D *> HBase;
   vector<TH1D *> HVariation;
   for(int i = 0; i < (int)Variations.size(); i++)
   {
      TH1D *H = (TH1D *)File.Get(Variations[i].c_str());
      TH1D *HB = (TH1D *)File.Get((Variations[i] + "Base").c_str());

      Assert(H != nullptr, ("Histogram for " + Labels[i] + " not found").c_str());
      Assert(HB != nullptr, ("Base histogram for " + Labels[i] + " not found").c_str());

      HB->SetStats(0);
      HB->SetLineWidth(2);
      HB->SetLineColor(Colors[0]);
      HB->SetMarkerColor(Colors[0]);
      HB->SetMarkerStyle(20);
      
      H->SetLineWidth(2);
      H->SetLineColor(Colors[(i+1)%7]);
      H->SetMarkerColor(Colors[(i+1)%7]);
      H->SetMarkerStyle(20);
      if(i + 1 >= 7)
         H->SetLineStyle(kDashed);

      HVariation.push_back(H);
      HBase.push_back(HB);
   }

   for(int i = 0; i < (int)Variations.size(); i++)
   {
      TCanvas Canvas;

      HBase[i]->SetTitle(("Variation for " + Labels[i]).c_str());
      HVariation[i]->SetTitle(("Variation for " + Labels[i]).c_str());
   
      HBase[i]->GetXaxis()->SetTitle("Unfolded bin index");
      HVariation[i]->GetXaxis()->SetTitle("Unfolded bin index");

      HBase[i]->Draw("");
      HBase[i]->Draw("hist same");
      HVariation[i]->Draw("same");
      HVariation[i]->Draw("hist same");

      TLegend Legend(0.5, 0.85, 0.8, 0.85 - 0.04 * 2);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(HBase[i], "Nominal", "pl");
      Legend.AddEntry(HVariation[i], "Variation", "pl");
      Legend.Draw();

      Canvas.SetGridx();
      Canvas.SetGridy();
      Canvas.SetLogy(false);
      PdfFile.AddCanvas(Canvas);
      
      HBase[i]->Draw("hist");
      HBase[i]->Draw("same");
      HVariation[i]->Draw("hist same");
      HVariation[i]->Draw("same");
      Legend.Draw();
      Canvas.SetLogy(true);
      PdfFile.AddCanvas(Canvas);

      HVariation[i]->Divide(HBase[i]);
      HVariation[i]->SetStats(0);
      HVariation[i]->GetYaxis()->SetTitle("Ratio to nominal");
      HVariation[i]->SetMinimum(0.75);
      HVariation[i]->SetMaximum(1.45);
      HVariation[i]->Draw();
      HVariation[i]->Draw("hist same");
      GLine.Draw("l");
      Canvas.SetLogy(false);
      PdfFile.AddCanvas(Canvas);
   }

   TCanvas Canvas;
   TLegend Legend1(0.5, 0.85, 0.8, 0.85 - 0.035 * 7);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   TLegend Legend2(0.2, 0.85, 0.5, 0.85 - 0.035 * 7);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);

   for(int i = 0; i < (int)Variations.size(); i++)
   {
      if(i < 7)
         Legend1.AddEntry(HVariation[i], Labels[i].c_str(), "pl");
      else
         Legend2.AddEntry(HVariation[i], Labels[i].c_str(), "pl");

      HVariation[i]->SetTitle("");

      if(i == 0)
         HVariation[i]->Draw();
      else
         HVariation[i]->Draw("same");
      HVariation[i]->Draw("hist same");
   }

   while(Legend1.GetNRows() < 7)
      Legend1.AddEntry("", "", "");
   while(Legend2.GetNRows() < 7)
      Legend2.AddEntry("", "", "");

   GLine.Draw("l");
   Legend1.Draw();
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   TH1D *HTotalPlus = (TH1D *)File.Get("HTotalPlus");
   PdfFile.AddPlot(HTotalPlus);
   TH1D *HTotalMinus = (TH1D *)File.Get("HTotalMinus");
   PdfFile.AddPlot(HTotalMinus);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




