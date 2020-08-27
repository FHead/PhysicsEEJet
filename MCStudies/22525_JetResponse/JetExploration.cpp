#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void Add1DPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log = false);
void Add2DPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, bool Log = false);
void Add1DProfile(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log = false);
void Add1DProfileRMS(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log = false);
void Add2DProfile(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, bool Log = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("FileName", "AllMatched.root");
   string ReverseFileName = CL.Get("ReverseFileName", "AllReverseMatched.root");

   PdfFileHelper PdfFile("JetResponse.pdf");
   PdfFile.AddTextPage("Jet property plots from MC");

   TFile File(FileName.c_str());
   TFile ReverseFile(ReverseFileName.c_str());

   TTree *Tree = (TTree *)File.Get("MatchedTree");
   TTree *ReverseTree = (TTree *)ReverseFile.Get("MatchedTree");

   char Cut[] = "GenPT > 5 && GenTheta > 0.7854 && GenTheta < 2.3562 && DR < 0.4";

   PdfFile.AddTextPage("Distributions");
   Add1DPlot(PdfFile, Tree, "GenTheta/3.1415926535", "", "",
      ";Gen jet #theta;", 100, 0, 1);
   Add1DPlot(PdfFile, Tree, "GenPT", "", "",
      ";Gen jet PT;", 100, 0, 50);
   Add1DPlot(PdfFile, Tree, "GenTheta/3.1415926535", "GenPT > 5", "",
      "GenPT > 5;Gen jet #theta;", 100, 0, 1);
   Add2DPlot(PdfFile, Tree, "GenPhi:GenTheta/3.1415926535", "GenPT > 5", "colz",
      "GenPT > 5;Gen jet #theta;Gen #phi", 100, 0, 1, 100, -M_PI, M_PI);
   Add1DPlot(PdfFile, Tree, "GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "",
      "Gen jet #theta = 0.25#pi-0.75#pi;Gen jet PT;", 100, 0, 50);
   Add1DPlot(PdfFile, Tree, "GenPhi", "GenPT > 5 && GenTheta > 0.7854 && GenTheta < 2.3562", "",
      "GenPT > 5, Gen jet #theta = 0.25#pi-0.75#pi;Gen jet #phi;", 100, -M_PI, M_PI);

   PdfFile.AddTextPage("Matching efficiency plots");
   Add1DProfile(PdfFile, Tree, "DR<0.4:GenTheta/3.1415926535", "GenPT > 5", "  ",
      "Gen PT > 5;Gen jet #theta/#pi;P(DR < 0.4)", 100, 0, 1);
   Add1DProfile(PdfFile, Tree, "DR<0.4:GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "  ",
      "Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;P(DR < 0.4)", 100, 0, 50);
   
   PdfFile.AddTextPage("Fake rate plots");
   // Note that reverse tree "Gen" = reco, "Reco" = gen
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4:GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "  ",
      "Reco #theta = 0.25#pi-0.75#pi;Reco jet PT;P(DR < 0.4)", 100, 0, 50);
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4:GenTheta/3.1415926535", "GenPT > 5", "  ",
      "Reco PT > 5;Reco jet #theta/#pi;P(DR < 0.4)", 100, 0, 1);
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4&&RecoPT>5:GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "  ",
      "Reco #theta = 0.25#pi-0.75#pi;Reco jet PT;P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 50);
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4&&RecoPT>5:GenTheta/3.1415926535", "GenPT > 5", "  ",
      "Reco PT > 5;Reco jet #theta/#pi;P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 1);
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4&&RecoPT>5:GenTheta/3.1415926535", "GenPT > 10", "  ",
      "Reco PT > 10;Reco jet #theta/#pi;P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 1);
   Add1DProfile(PdfFile, ReverseTree, "1-(DR<0.4&&RecoPT>5):GenTheta/3.1415926535", "GenPT > 10", "  ",
      "Reco PT > 10;Reco jet #theta/#pi;1 - P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 1);
   Add1DProfile(PdfFile, ReverseTree, "1-(DR<0.4&&RecoPT>5):GenTheta/3.1415926535", "GenPT > 12", "  ",
      "Reco PT > 12;Reco jet #theta/#pi;1 - P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 1);
   Add1DProfile(PdfFile, ReverseTree, "DR<0.4&&RecoPT>5:GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "  ",
      "Reco #theta = 0.25-0.75#pi;Reco jet PT;P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 50);
   Add1DProfile(PdfFile, ReverseTree, "1-(DR<0.4&&RecoPT>5):GenPT", "GenTheta > 0.7854 && GenTheta < 2.3562", "  ",
      "Reco #theta = 0.25-0.75#pi;Reco jet PT;1 - P(DR < 0.4 && Matched Gen PT > 5)", 100, 0, 50, true);

   PdfFile.AddTextPage("Jet response plots");
   Add2DPlot(PdfFile, Tree, "RecoPT/GenPT:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "colz",
      "Gen PT > 5;Gen jet #theta;Jet response", 100, 0, 1, 100, 0, 2);
   Add1DProfileRMS(PdfFile, Tree, "RecoPT/GenPT:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "  ",
      "Gen PT > 5;Gen jet #theta;Jet response", 100, 0, 1);
   Add2DPlot(PdfFile, Tree, "RecoPT/GenPT:GenPT", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet response", 100, 0, 50, 100, 0, 2);
   Add1DProfileRMS(PdfFile, Tree, "RecoPT/GenPT:GenPT", Cut, "  ",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet response", 100, 0, 50);
   Add1DPlot(PdfFile, Tree, "GenN", Cut, "",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet N;", 30, 0, 30);
   Add2DPlot(PdfFile, Tree, "RecoPT/GenPT:GenN", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet N;Jet response", 30, 0, 30, 100, 0, 2);
   Add1DProfileRMS(PdfFile, Tree, "RecoPT/GenPT:GenN", Cut, "  ",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet N;Jet response", 30, 0, 30);
   Add1DPlot(PdfFile, Tree, "RecoN", Cut, "",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Reco jet N;", 25, 0, 25);
   Add2DPlot(PdfFile, Tree, "RecoPT/GenPT:RecoN", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Reco jet N;Jet response", 25, 0, 25, 100, 0, 2);
   Add1DProfileRMS(PdfFile, Tree, "RecoPT/GenPT:RecoN", Cut, "  ",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Reco jet N;Jet response", 25, 0, 25);

   Tree->SetAlias("DPhiRaw", "(RecoPhi-GenPhi)");
   Tree->SetAlias("DPhi", "(DPhiRaw+(DPhiRaw<-3.1415926535)*2*3.1415926535-(DPhiRaw>3.1415926535)*2*3.1415926535)");

   PdfFile.AddTextPage("Jet angular resolution plots");
   Add2DPlot(PdfFile, Tree, "RecoTheta-GenTheta:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "colz",
      "Gen PT > 5;Gen jet #theta/#pi;Jet theta difference (reco-gen)", 100, 0, 1, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "RecoTheta-GenTheta:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "colz",
      "Gen PT > 5;Gen jet #theta/#pi;Jet theta difference (reco-gen)", 100, 0, 1);
   Add2DPlot(PdfFile, Tree, "RecoTheta-GenTheta:GenPT", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet theta difference (reco-gen)", 100, 0, 50, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "RecoTheta-GenTheta:GenPT", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet theta difference (reco-gen)", 100, 0, 50);
   Add2DPlot(PdfFile, Tree, "RecoTheta-GenTheta:GenPhi", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet #phi;Jet theta difference (reco-gen)", 100, -M_PI, M_PI, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "RecoTheta-GenTheta:GenPhi", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet #phi;Jet theta difference (reco-gen)", 100, -M_PI, M_PI);
   Add2DPlot(PdfFile, Tree, "DPhi:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "colz",
      "Gen PT > 5;Gen jet #theta/#pi;Jet phi difference (reco-gen)", 100, 0, 1, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "DPhi:GenTheta/3.1415926535", "GenPT > 5 && DR < 0.4", "colz",
      "Gen PT > 5;Gen jet #theta/#pi;Jet phi difference (reco-gen)", 100, 0, 1);
   Add2DPlot(PdfFile, Tree, "DPhi:GenPT", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet phi difference (reco-gen)", 100, 0, 50, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "DPhi:GenPT", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet PT;Jet phi difference (reco-gen)", 100, 0, 50);
   Add2DPlot(PdfFile, Tree, "DPhi:GenPhi", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet #phi;Jet phi difference (reco-gen)", 100, -M_PI, M_PI, 100, -0.25, 0.25);
   Add1DProfileRMS(PdfFile, Tree, "DPhi:GenPhi", Cut, "colz",
      "Gen PT > 5, Gen #theta = 0.25#pi-0.75#pi;Gen jet #phi;Jet phi difference (reco-gen)", 100, -M_PI, M_PI);

   ReverseFile.Close();
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Add1DPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log)
{
   TH1D H("H", Title.c_str(), N, Min, Max);
   H.SetStats(0);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str(), "");

   PdfFile.AddPlot(H, Option.c_str(), Log);
}

void Add2DPlot(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, bool Log)
{
   TH2D H("H", Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   H.SetStats(0);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str(), "colz");

   PdfFile.AddPlot(H, Option.c_str(), false, Log);
}

void Add1DProfileRMS(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log)
{
   TProfile H("H", Title.c_str(), N, Min, Max);
   TProfile H2("H2", Title.c_str(), N, Min, Max, "S");
   H.SetStats(0);
   H2.SetStats(0);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str(), "prof");
   Tree->Draw((ToPlot + ">>H2").c_str(), Selection.c_str(), "prof");

   PdfFile.AddPlot(H, Option.c_str(), Log);

   TGraph G;
   for(int i = 1; i <= N; i++)
   {
      double x = H2.GetXaxis()->GetBinCenter(i);
      double y = H2.GetBinError(i);
      G.SetPoint(i - 1, x, y);
   }
   G.SetTitle((string(H2.GetTitle()) + " (RMS)").c_str());
   G.GetXaxis()->SetTitle(H2.GetXaxis()->GetTitle());
   G.GetYaxis()->SetTitle((string(H2.GetYaxis()->GetTitle()) + " RMS").c_str());

   PdfFile.AddPlot(G, "ap", Log);
}

void Add1DProfile(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int N, double Min, double Max, bool Log)
{
   TProfile H("H", Title.c_str(), N, Min, Max, "");
   H.SetStats(0);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str(), "prof");

   PdfFile.AddPlot(H, Option.c_str(), Log);
}

void Add2DProfile(PdfFileHelper &PdfFile, TTree *Tree, string ToPlot, string Selection, string Option,
   string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY, bool Log)
{
   TProfile2D H("H", Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   H.SetStats(0);

   Tree->Draw((ToPlot + ">>H").c_str(), Selection.c_str(), "prof2d");

   PdfFile.AddPlot(H, Option.c_str(), false, Log);
}






