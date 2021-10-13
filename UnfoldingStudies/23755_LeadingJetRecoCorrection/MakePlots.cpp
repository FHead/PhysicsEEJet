#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string GenPassFileName  = CL.Get("GenPass", "Input/MCPythia6LeadingDiJetE.root");
   string BothPassFileName = CL.Get("BothPass", "Input/MCLeadingDiJetENominal.root");

   string OutputFileName   = CL.Get("Output", "Result.pdf");
   string DHFileName       = CL.Get("DHFile", "Step1Correction.dh");
   string DHFileState      = CL.Get("State", "LeadingDiJetE");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("The missing correction");

   TFile GenPassFile(GenPassFileName.c_str());
   TFile BothPassFile(BothPassFileName.c_str());

   TH1D *GenPass = (TH1D *)GenPassFile.Get("HMCGen");
   TH1D *BothPass = (TH1D *)BothPassFile.Get("HMCGen");

   GenPass->GetXaxis()->SetTitle("Bin index");

   TCanvas Canvas;

   GenPass->SetStats(0);
   BothPass->SetStats(0);

   GenPass->SetLineColor(Colors[0]);
   GenPass->SetLineWidth(2);
   BothPass->SetLineColor(Colors[1]);
   BothPass->SetLineWidth(2);

   GenPass->Draw();
   BothPass->Draw("same");

   PdfFile.AddCanvas(Canvas);

   DataHelper DHFile(DHFileName);

   DHFile[DHFileState]["N"] = GenPass->GetNbinsX();
   for(int i = 1; i <= GenPass->GetNbinsX(); i++)
   {
      DHFile[DHFileState][Form("G%d",i)] = GenPass->GetBinContent(i);
      DHFile[DHFileState][Form("B%d",i)] = BothPass->GetBinContent(i);
      double R = GenPass->GetBinContent(i) / BothPass->GetBinContent(i);
      if(BothPass->GetBinContent(i) == 0)
         R = 1;
      DHFile[DHFileState][Form("R%d",i)] = R;
   }

   DHFile.SaveToFile();

   GenPass->Divide(BothPass);
   GenPass->GetYaxis()->SetTitle("Ratio");

   PdfFile.AddPlot(GenPass);

   BothPassFile.Close();
   GenPassFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




