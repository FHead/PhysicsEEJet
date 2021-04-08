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
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input", "MCNoCut.root");
   string Tier           = CL.Get("Tier", "Gen");
   string OutputFileName = CL.Get("Output", "MeowCut.root");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Leading DiJet Cut Investigation");

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get("UnfoldingTree");

   PdfFile.AddPlot(Tree, Tier + "JetTheta", "", "", Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, Tier + "JetTheta[0]", "", "", "Leading " + Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, Tier + "JetTheta[1]", "", "", "Subleading " + Tier + " Jet Theta;#theta;", 100, 0, M_PI);
   PdfFile.AddPlot(Tree, Tier + "ESum", "", "", "Total " + Tier + " energy within 0.2-0.8#pi;E (GeV);", 100, 0, 91.5);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading jet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading jet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading jet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of subleading jet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of subleading jet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of subleading jet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159&&" + Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading dijet within 0.2-0.8#pi;E (GeV);", 100, 0, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159&&" + Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading dijet within 0.2-0.8#pi;E (GeV);", 100, 70, 91.2);
   PdfFile.AddPlotProfile(Tree, Tier + "JetTheta[0]>0.2*3.14159&&" + Tier + "JetTheta[0]<0.8*3.14159&&" + Tier + "JetTheta[1]>0.2*3.14159&&" + Tier + "JetTheta[1]<0.8*3.14159:" + Tier + "ESum", "", "prof",
      "Fraction of leading dijet within 0.2-0.8#pi;E (GeV);", 50, 80, 91.2);

   TH1D HESum("HESum", ";E_{sum} Cut;Cut efficiency", 500, 0, 91.2);
   Tree->Draw((Tier + "ESum>>HESum").c_str());
   for(int i = HESum.GetNbinsX() - 1; i >= 1; i--)
      HESum.SetBinContent(i, HESum.GetBinContent(i) + HESum.GetBinContent(i + 1));
   HESum.Scale(1 / HESum.GetBinContent(1));
   HESum.SetStats(0);
   PdfFile.AddPlot(HESum, "", false, false, true);

   InputFile.Close();
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




