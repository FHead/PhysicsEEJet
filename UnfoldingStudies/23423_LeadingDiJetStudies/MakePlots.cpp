#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input", "MCNoCut.root");
   string Tier           = CL.Get("Tier", "Gen");
   string OutputFileName = CL.Get("Output", "MeowCut.root");
   string Acceptance     = CL.Get("Acceptance", "020");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Leading DiJet Cut Investigation");

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get("UnfoldingTree");

   Tree->SetAlias("TargetSumE", (Tier + "SumE" + Acceptance).c_str());
   Tree->SetAlias("TargetJetTheta", (Tier + "JetTheta").c_str());
   Tree->SetAlias("Jet1Cut", "(TargetJetTheta[0] > 0.2 * 3.14159 && TargetJetTheta[0] < 0.8 * 3.14159)");
   Tree->SetAlias("Jet2Cut", "(TargetJetTheta[1] > 0.2 * 3.14159 && TargetJetTheta[1] < 0.8 * 3.14159)");
   Tree->SetAlias("Jet12Cut", "(Jet1Cut && Jet2Cut)");

   PdfFile.AddPlot(Tree, "TargetJetTheta", "", "", Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, "TargetJetTheta[0]", "", "", "Leading " + Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, "TargetJetTheta[1]", "", "", "Subleading " + Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, "TargetSumE", "", "", "Total " + Tier + " energy within 0.2-0.8#pi;E (GeV);", 100, 0, 91.5);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      "Fraction of events with leading jet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      "Fraction of events with leading jet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      "Fraction of events with leading jet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet1Cut:TargetSumE", "", "prof",
      ";E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      "Fraction of events with subleading jet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      "Fraction of events with subleading jet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      "Fraction of events with subleading jet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet2Cut:TargetSumE", "", "prof",
      ";E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      "Fraction of events with leading dijet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      "Fraction of events with leading dijet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      ";E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      "Fraction of events with leading dijet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      ";E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      "Fraction of events with leading dijet within 0.2-0.8#pi;E (GeV);", 50, 88, 91.2);
   PdfFile.AddPlotProfile(Tree, "Jet12Cut:TargetSumE", "", "prof",
      ";E (GeV);", 50, 88, 91.2);

   TH1D HSumE("HSumE", ";E_{sum} Cut;Cut efficiency", 500, 0, 91.2);
   Tree->Draw((Tier + "SumE>>HSumE").c_str());
   for(int i = HSumE.GetNbinsX() - 1; i >= 1; i--)
      HSumE.SetBinContent(i, HSumE.GetBinContent(i) + HSumE.GetBinContent(i + 1));
   HSumE.Scale(1 / HSumE.GetBinContent(1));
   HSumE.SetStats(0);
   PdfFile.AddPlot(HSumE, "", false, false, true);

   InputFile.Close();
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




