#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);

int main(int argc, char *argv[])
{
   SetThumbStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);
   string InputFileName    = CL.Get("Input");
   string OutputFileName   = CL.Get("Output");
   double JetThetaGap      = CL.GetDouble("JetThetaGap", 0.2);
   bool RecalculateSumE    = CL.GetBool("RecalculateSumE", false);
   double ParticleThetaGap = RecalculateSumE ? CL.GetDouble("ParticleThetaGap") : 0;
   string SumEString       = RecalculateSumE ? "GenSumE[0]" : CL.Get("SumEString");
   string Tier             = CL.Get("Tier", "Gen");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Leading jets");

   PdfFile.AddTextPage(
   {
      string(Form("Jet theta: %.2f#pi - %.2f#pi", JetThetaGap, 1 - JetThetaGap)),
      string(Form("Particle theta: %.2f#pi - %.2f#pi", ParticleThetaGap, 1 - ParticleThetaGap))
   });

   string JetThetaCut1 = Form("(GenJetTheta[0]>%f&&GenJetTheta[0]<%f)", JetThetaGap * M_PI, (1 - JetThetaGap) * M_PI);
   string JetThetaCut2 = Form("(GenJetTheta[1]>%f&&GenJetTheta[1]<%f)", JetThetaGap * M_PI, (1 - JetThetaGap) * M_PI);
   string JetThetaCut  = "(" + JetThetaCut1 + "&&" + JetThetaCut2 + ")";

   string OnlySumE = "";
   if(RecalculateSumE == true)
      OnlySumE = Form("(Sum$(GenE*(GenTheta>%f&&GenTheta<%f&&GenStatus==1)))", ParticleThetaGap * M_PI, (1 - ParticleThetaGap) * M_PI);
   else
      OnlySumE = Form("(%s)", SumEString.c_str());
   string SumECut = "(" + OnlySumE + " > 83 && " + JetThetaCut + ")";

   TFile InputFile(InputFileName.c_str());

   TH1D HA1("HA1", "Leading jet;Jet E;", 40, 10, 50);
   TH1D HB1("HB1", "Leading jet;Jet E;", 40, 10, 50);
   TH1D HA2("HA2", "Subleading jet;Jet E;", 40, 10, 50);
   TH1D HB2("HB2", "Subleading jet;Jet E;", 40, 10, 50);
   TH1D HA12("HA12", "Leading dijet;Jet E;", 40, 10, 50);
   TH1D HB12("HB12", "Leading dijet;Jet E;", 40, 10, 50);
   TH1D HAS("HAS", "Leading dijet;Dijet sum E;", 40, 20, 95);
   TH1D HBS("HBS", "Leading dijet;Dijet sum E;", 40, 20, 95);

   HA1.Sumw2();
   HB1.Sumw2();
   HA2.Sumw2();
   HB2.Sumw2();
   HA12.Sumw2();
   HB12.Sumw2();
   HAS.Sumw2();
   HBS.Sumw2();

   TTree *Tree = (TTree *)InputFile.Get("UnfoldingTree");
   Tree->Draw("GenJetE[0]>>HA1",              SumECut.c_str(),     "");
   Tree->Draw("GenJetE[0]>>HB1",              JetThetaCut.c_str(), "");
   Tree->Draw("GenJetE[1]>>HA2",              SumECut.c_str(),     "");
   Tree->Draw("GenJetE[1]>>HB2",              JetThetaCut.c_str(), "");
   Tree->Draw("(GenJetE[0]+GenJetE[1])>>HAS", SumECut.c_str(),     "");
   Tree->Draw("(GenJetE[0]+GenJetE[1])>>HBS", JetThetaCut.c_str(), "");

   HA12.Add(&HA1);
   HA12.Add(&HA2);
   HB12.Add(&HB1);
   HB12.Add(&HB2);

   AddPlot(PdfFile, HA1, HB1);
   AddPlot(PdfFile, HA2, HB2);
   AddPlot(PdfFile, HA12, HB12);
   AddPlot(PdfFile, HAS, HBS);

   Tree->SetAlias("TargetSumE", OnlySumE.c_str());
   Tree->SetAlias("TargetJetTheta", (Tier + "JetTheta").c_str());
   Tree->SetAlias("Jet1Cut", JetThetaCut1.c_str());
   Tree->SetAlias("Jet2Cut", JetThetaCut2.c_str());
   Tree->SetAlias("Jet12Cut", JetThetaCut.c_str());

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

   TH1D HSumE("HSumE", ";E Cut;Cut efficiency", 500, 0, 91.2);
   Tree->Draw((OnlySumE + ">>HSumE").c_str());
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

void AddPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   static vector<int> Colors;
   if(Colors.size() == 0)
      Colors = GetPrimaryColors();
   
   H1.SetStats(0);
   H2.SetStats(0);
   
   H1.SetLineWidth(2);
   H1.SetLineColor(Colors[1]);
   H1.SetMarkerStyle(20);
   H1.SetMarkerColor(Colors[1]);
   H2.SetLineWidth(2);
   H2.SetLineColor(Colors[0]);
   H2.SetMarkerStyle(20);
   H2.SetMarkerColor(Colors[0]);

   // H1.Scale(1 / H1.Integral());
   // H2.Scale(1 / H2.Integral());

   TLegend Legend(0.4, 0.2, 0.7, 0.4);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "With SumE Cut", "pl");
   Legend.AddEntry(&H2, "Without SumE Cut", "pl");

   TCanvas Canvas;

   H1.Draw();
   H2.Draw("same");
   Legend.Draw();

   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   TGraphAsymmErrors G;
   G.Divide(&H1, &H2);

   G.SetMarkerColor(Colors[5]);
   G.SetLineColor(Colors[5]);

   G.GetYaxis()->SetTitle("With Cut / Without Cut");
   G.GetXaxis()->SetTitle(H1.GetXaxis()->GetTitle());

   G.Draw("ap");

   G.GetYaxis()->SetRangeUser(0.3, 1.1);

   Canvas.SetGridx();
   Canvas.SetGridy();
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
}

