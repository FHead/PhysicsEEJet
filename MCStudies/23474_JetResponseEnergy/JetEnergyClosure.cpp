#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void PlotEClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double EMin, double EMax, double R);
void PlotThetaClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double EMin, double EMax, double R);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Name", "AllMatched.root");
   string OutputFileName = CL.Get("Output", "JECClosure.pdf");
   double R = CL.GetDouble("R", 0.4);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet energy closure plots from MC");

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("MatchedTree");

   PlotEClosure(PdfFile, Tree, 0.00, 0.10, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.10, 0.15, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.15, 0.20, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.20, 0.25, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.25, 0.30, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.30, 0.35, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.35, 0.40, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.40, 0.45, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.45, 0.50, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.50, 0.55, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.55, 0.60, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.60, 0.65, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.65, 0.70, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.70, 0.75, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.75, 0.80, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.80, 0.85, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.85, 0.90, 0, 50, R);
   PlotEClosure(PdfFile, Tree, 0.90, 1.00, 0, 50, R);
   
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00,  5, 10, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 10, 15, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 15, 20, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 20, 25, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 25, 30, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 30, 35, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 35, 40, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 40, 45, R);
   PlotThetaClosure(PdfFile, Tree, 0.00, 1.00, 45, 50, R);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotEClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double EMin, double EMax, double R)
{
   double ThetaMin = ThetaPIMin * M_PI;
   double ThetaMax = ThetaPIMax * M_PI;

   TProfile P1("P1", ";Gen E;Response", 50, EMin, EMax);
   TProfile P2("P2", ";Gen E;Response", 50, EMin, EMax);

   double Threshold = (R < 0.6) ? 0.2 : 0.37;

   Tree->Draw("RecoE/GenE:GenE>>P1", Form("GenTheta > %f && GenTheta < %f && 1-cos(Angle) < %f", ThetaMin, ThetaMax, Threshold));
   Tree->Draw("CorrectedE/GenE:GenE>>P2", Form("GenTheta > %f && GenTheta < %f && 1-cos(Angle) < %f", ThetaMin, ThetaMax, Threshold));

   P2.SetLineWidth(2);
   P2.SetLineColor(kBlack);
   P2.SetMarkerColor(kBlack);
   P2.SetMarkerSize(2);
   P1.SetLineWidth(2);
   P1.SetLineColor(kRed);
   P1.SetMarkerColor(kRed);
   P1.SetMarkerSize(2);

   for(int i = 1; i <= 50; i++)
   {
      if(P1.GetBinEntries(i) == 1)
         P1.SetBinContent(i, 0);
      if(P2.GetBinEntries(i) == 1)
         P2.SetBinContent(i, 0);
   }

   TGraph G1;
   G1.SetPoint(0, -1000, 1);
   G1.SetPoint(1, +1000, 1);

   TGraph G2;
   G2.SetPoint(0, -1000, 1.01);
   G2.SetPoint(1, +1000, 1.01);
   G2.SetPoint(2, +1000, 0.99);
   G2.SetPoint(3, -1000, 0.99);
   G2.SetLineStyle(kDashed);

   TH2D HWorld("HWorld", ";Gen E;Response", 50, EMin, EMax, 50, 0.75, 1.25);
   HWorld.SetStats(0);
   HWorld.GetYaxis()->SetNdivisions(505);
   HWorld.GetXaxis()->SetNdivisions(505);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G1.Draw("l");
   G2.Draw("l");

   P1.Draw("same");
   P2.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.06);
   Latex.SetNDC();
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.20, 0.82, "#color[2]{Raw} #color[1]{Corrected}");
   Latex.DrawLatex(0.20, 0.75, Form("Theta = %.2f#pi ~ %.2f#pi", ThetaPIMin, ThetaPIMax));

   PdfFile.AddCanvas(Canvas);
}

void PlotThetaClosure(PdfFileHelper &PdfFile, TTree *Tree,
   double ThetaPIMin, double ThetaPIMax, double EMin, double EMax, double R)
{
   double ThetaMin = ThetaPIMin * M_PI;
   double ThetaMax = ThetaPIMax * M_PI;

   TProfile P1("P1", ";Gen Theta (#pi);Response", 50, ThetaPIMin, ThetaPIMax);
   TProfile P2("P2", ";Gen Theta (#pi);Response", 50, ThetaPIMin, ThetaPIMax);

   double Threshold = (R < 0.6) ? 0.2 : 0.37;

   Tree->Draw("RecoE/GenE:GenTheta/3.1415926535>>P1", Form("GenE > %f && GenE < %f && 1-cos(Angle) < %f", EMin, EMax, Threshold));
   Tree->Draw("CorrectedE/GenE:GenTheta/3.1415926535>>P2", Form("GenE > %f && GenE < %f && 1-cos(Angle) < %f", EMin, EMax, Threshold));

   P2.SetLineWidth(2);
   P2.SetLineColor(kBlack);
   P2.SetMarkerColor(kBlack);
   P2.SetMarkerSize(2);
   P1.SetLineWidth(2);
   P1.SetLineColor(kRed);
   P1.SetMarkerColor(kRed);
   P1.SetMarkerSize(2);

   for(int i = 1; i <= 50; i++)
   {
      if(P1.GetBinEntries(i) == 1)
         P1.SetBinContent(i, 0);
      if(P2.GetBinEntries(i) == 1)
         P2.SetBinContent(i, 0);
   }

   TGraph G1;
   G1.SetPoint(0, -1000, 1);
   G1.SetPoint(1, +1000, 1);

   TGraph G2;
   G2.SetPoint(0, -1000, 1.01);
   G2.SetPoint(1, +1000, 1.01);
   G2.SetPoint(2, +1000, 0.99);
   G2.SetPoint(3, -1000, 0.99);
   G2.SetLineStyle(kDashed);
   
   TH2D HWorld("HWorld", ";Gen Theta (#pi);Response", 50, ThetaPIMin, ThetaPIMax, 50, 0.75, 1.25);
   HWorld.SetStats(0);
   HWorld.GetYaxis()->SetNdivisions(505);
   HWorld.GetXaxis()->SetNdivisions(505);

   TCanvas Canvas;

   HWorld.Draw("axis");

   G1.Draw("l");
   G2.Draw("l");

   P1.Draw("same");
   P2.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.06);
   Latex.SetNDC();
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.20, 0.82, "#color[2]{Raw} #color[1]{Corrected}");
   Latex.DrawLatex(0.20, 0.75, Form("E = %.1f ~ %.1f GeV", EMin, EMax));

   PdfFile.AddCanvas(Canvas);
}















