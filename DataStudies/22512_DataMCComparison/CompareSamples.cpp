#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TH1D.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void ComparePlots(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Cut,
   string Title, int N, double Min, double Max, bool LogY = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DataFileName   = CL.Get("Data");
   string MCFileName     = CL.Get("MC");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Data/MC comparisons");

   TFile FData(DataFileName.c_str());
   TFile FMC(MCFileName.c_str());

   TTree *TData = (TTree *)FData.Get("Tree");
   TTree *TMC   = (TTree *)FMC.Get("Tree");

   ComparePlots(PdfFile, TData, TMC, "JetPT", "JetTheta > 0.2*3.14159 && JetTheta < 0.8*3.14159",
      "JetTheta = 0.2#pi - 0.8#pi;Jet PT", 100, 0, 75, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 5",
      "JetPT < 5;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 10 && JetPT > 5",
      "JetPT = 5 - 10;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 15 && JetPT > 10",
      "JetPT = 10 - 15;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 20 && JetPT > 15",
      "JetPT = 15 - 20;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 25 && JetPT > 20",
      "JetPT = 20 - 25;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 30 && JetPT > 25",
      "JetPT = 25 - 30;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 35 && JetPT > 30",
      "JetPT = 30 - 35;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 40 && JetPT > 35",
      "JetPT = 35 - 40;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 45 && JetPT > 40",
      "JetPT = 40 - 45;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT < 50 && JetPT > 45",
      "JetPT = 45 - 50;Jet Theta (#pi)", 100, 0, 1, true);
   ComparePlots(PdfFile, TData, TMC, "JetTheta/3.14159", "JetPT > 50",
      "JetPT > 50;Jet Theta (#pi)", 100, 0, 1, true);

   FMC.Close();
   FData.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ComparePlots(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Cut,
   string Title, int N, double Min, double Max, bool LogY)
{
   TH1D H1("H1", Title.c_str(), N, Min, Max);
   TH1D H2("H2", Title.c_str(), N, Min, Max);

   H1.SetStats(0);
   H2.SetStats(0);

   H2.SetMarkerColor(kRed);
   H2.SetLineColor(kRed);

   T1->Draw((ToPlot + ">>H1").c_str(), Cut.c_str());
   T2->Draw((ToPlot + ">>H2").c_str(), Cut.c_str());

   H1.Scale(1 / H1.Integral() / ((Max - Min) / N));
   H2.Scale(1 / H2.Integral() / ((Max - Min) / N));

   TCanvas Canvas;

   H1.Draw();
   H2.Draw("same");

   Canvas.SetLogy(LogY);

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.12, 0.87, "#color[1]{Data} #color[2]{MC}");

   PdfFile.AddCanvas(Canvas);

   Canvas.SetLogy(false);

   H1.Divide(&H2);
   H1.Draw();

   H1.GetYaxis()->SetTitle("Data / MC");

   H1.SetMinimum(0.5);
   H1.SetMaximum(1.5);

   PdfFile.AddCanvas(Canvas);
}



