#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TProfile.h"
#include "TGraphErrors.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
pair<double, double> GetR(PdfFileHelper &PdfFile, TTree *TData, TTree *TMC, double MinJ2PT, double MaxJ2PT, double MaxJ3PT);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DataFileName = CL.Get("Data", "DataSkimmed.root");
   string MCFileName = CL.Get("MC", "MCSkimmed.root");
   string OutputFileName = CL.Get("Output", "ZResidual.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Residual from Z's");

   TFile DataFile(DataFileName.c_str());
   TFile MCFile(MCFileName.c_str());

   TTree *DataTree = (TTree *)DataFile.Get("SkimmedTree");
   TTree *MCTree = (TTree *)MCFile.Get("SkimmedTree");

   GetR(PdfFile, DataTree, MCTree, 0, 20, 5);

   TGraphErrors G;

   G.GetXaxis()->SetTitle("J2PT");
   G.GetYaxis()->SetTitle("MC/Data");

   for(int i = 10; i < 44; i = i + 2)
   {
      pair<double, double> R = GetR(PdfFile, DataTree, MCTree, i, i + 2, 2);

      int N = G.GetN();
      G.SetPoint(N, i + 1, sqrt(R.first));
      G.SetPointError(N, 1, R.second);
   }

   TF1 F("F", "pol3", 12, 44);
   F.SetParameters(1, 0, 0, 0);

   G.Fit(&F);

   TCanvas Canvas;

   G.Draw("ap");
   F.Draw("same");
   PdfFile.AddCanvas(Canvas);

   ofstream out("Snippet.txt");
   out << F.GetParameter(0)
      << " " << F.GetParameter(1)
      << " " << F.GetParameter(2)
      << " " << F.GetParameter(3);
   out.close();

   MCFile.Close();
   DataFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

pair<double, double> GetR(PdfFileHelper &PdfFile, TTree *TData, TTree *TMC, double MinJ2PT, double MaxJ2PT, double MaxJ3PT)
{
   TProfile PData("PData", Form("%.1f ~ %.1f;J3PT;", MinJ2PT, MaxJ2PT), 30, 0.2, MaxJ3PT);
   TProfile PMC("PMC", Form("%.1f ~ %.1f;J3PT;", MinJ2PT, MaxJ2PT), 30, 0.2, MaxJ3PT);

   PMC.SetLineColor(kRed);
   PMC.SetMarkerColor(kRed);

   PData.SetStats(0);
   PMC.SetStats(0);

   char Cut[] = "J1Theta > 0.25*3.14159 && J1Theta < 0.75*3.14159 && J2Theta > 0.25*3.14159 && J2Theta < 0.75 * 3.14159";
   TData->Draw("M12:J3PT>>PData", Form("%s && J2PT > %f && J2PT < %f", Cut, MinJ2PT, MaxJ2PT), "prof");
   TMC->Draw("M12:J3PT>>PMC",     Form("%s && J2PT > %f && J2PT < %f", Cut, MinJ2PT, MaxJ2PT), "prof");

   TF1 FData("FData", "pol1");
   TF1 FMC("FMC", "pol1");

   FData.SetLineColor(kBlack);
   FMC.SetLineColor(kRed);

   PData.Fit(&FData);
   PMC.Fit(&FMC);

   TCanvas Canvas;

   PData.Draw("");
   PMC.Draw("same");

   PdfFile.AddCanvas(Canvas);

   double R = FMC.GetParameter(0) / FData.GetParameter(0);
   double MCRel = FMC.GetParError(0) / FMC.GetParameter(0);
   double DataRel = FData.GetParError(0) / FData.GetParameter(0);
   double Rel = sqrt(MCRel * MCRel + DataRel * DataRel);
   double Error = R * Rel;

   return pair<double, double>(R, Error);
}


