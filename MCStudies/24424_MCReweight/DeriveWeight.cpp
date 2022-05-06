#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "ProgressBar.h"
#include "SetStyle.h"
#include "PlotHelper4.h"

class Jet;
int main(int argc, char *argv[]);
void ReadJets(string FileName, vector<Jet> &Jets,
   double MinJetE = 0.0, double MaxJetE = 100.0,
   double MinJetTheta = 0, double MaxJetTheta = M_PI);
void AddPlot(PdfFileHelper &PdfFile, vector<Jet> &Jets, vector<Jet> &Base, double MinJetE, double MaxJetE,
   int N, double Min, double Max);
void SetHistogram(TH1D &H, int Color);
void AddComparisonPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);

class Jet
{
public:
   float E, Theta, Phi;
   int N00, N05, N10, N15;
public:
   Jet()  {}
   ~Jet() {}
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string BaseFileName = CL.Get("Base");
   string OutputFileName = CL.Get("Output");

   vector<Jet> InputJets, BaseJets;

   ReadJets(InputFileName, InputJets, 10, 100, 0.2 * M_PI, 0.8 * M_PI);
   ReadJets(BaseFileName,  BaseJets,  10, 100, 0.2 * M_PI, 0.8 * M_PI);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Multiplicity ratio");

   AddPlot(PdfFile, InputJets, BaseJets, 10, 20, 25, 0, 25);
   AddPlot(PdfFile, InputJets, BaseJets, 20, 30, 25, 0, 25);
   AddPlot(PdfFile, InputJets, BaseJets, 30, 40, 25, 0, 25);
   AddPlot(PdfFile, InputJets, BaseJets, 40, 50, 25, 0, 25);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}

void ReadJets(string FileName, vector<Jet> &Jets,
   double MinJetE, double MaxJetE,
   double MinJetTheta, double MaxJetTheta)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTree");
   if(Tree == nullptr)
   {
      File.Close();
      return;
   }

   int NGenJets;
   vector<float> *GenJetE = nullptr;
   vector<float> *GenJetTheta = nullptr;
   vector<float> *GenJetPhi = nullptr;
   vector<int> *GenJetN00 = nullptr;
   vector<int> *GenJetN05 = nullptr;
   vector<int> *GenJetN10 = nullptr;
   vector<int> *GenJetN15 = nullptr;

   Tree->SetBranchAddress("NGenJets", &NGenJets);
   Tree->SetBranchAddress("GenJetE", &GenJetE);
   Tree->SetBranchAddress("GenJetTheta", &GenJetTheta);
   Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
   Tree->SetBranchAddress("GenJetN00", &GenJetN00);
   Tree->SetBranchAddress("GenJetN05", &GenJetN05);
   Tree->SetBranchAddress("GenJetN10", &GenJetN10);
   Tree->SetBranchAddress("GenJetN15", &GenJetN15);

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      for(int iJ = 0; iJ < NGenJets; iJ++)
      {
         if((*GenJetE)[iJ] < MinJetE)
            continue;
         if((*GenJetTheta)[iJ] < MinJetTheta)
            continue;
         if((*GenJetTheta)[iJ] > MaxJetTheta)
            continue;

         Jet NewJet;
         NewJet.E = (*GenJetE)[iJ];
         NewJet.Theta = (*GenJetTheta)[iJ];
         NewJet.Phi = (*GenJetPhi)[iJ];
         NewJet.N00 = (*GenJetN00)[iJ];
         NewJet.N05 = (*GenJetN05)[iJ];
         NewJet.N10 = (*GenJetN10)[iJ];
         NewJet.N15 = (*GenJetN15)[iJ];

         Jets.push_back(NewJet);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();
}

void AddPlot(PdfFileHelper &PdfFile, vector<Jet> &Jets, vector<Jet> &Base, double MinJetE, double MaxJetE,
   int N, double Min, double Max)
{
   PdfFile.AddTextPage(Form("Energy range %.1f-%.1f", MinJetE, MaxJetE));

   static vector<int> Colors = GetPrimaryColors();

   TH1D H1_N05("H1_N05", "N(E > 0.5);Multiplicity;", N, Min, Max);
   TH1D H2_N05("H2_N05", "N(E > 0.5);Multiplicity;", N, Min, Max);
   TH1D H1_N10("H1_N10", "N(E > 1.0);Multiplicity;", N, Min, Max);
   TH1D H2_N10("H2_N10", "N(E > 1.0);Multiplicity;", N, Min, Max);
   TH1D H1_N15("H1_N15", "N(E > 1.5);Multiplicity;", N, Min, Max);
   TH1D H2_N15("H2_N15", "N(E > 1.5);Multiplicity;", N, Min, Max);

   for(Jet &J : Jets)
   {
      if(J.E > MinJetE && J.E <= MaxJetE)
      {
         H1_N05.Fill(J.N05);
         H1_N10.Fill(J.N10);
         H1_N15.Fill(J.N15);
      }
   }
   for(Jet &J : Base)
   {
      if(J.E > MinJetE && J.E <= MaxJetE)
      {
         H2_N05.Fill(J.N05);
         H2_N10.Fill(J.N10);
         H2_N15.Fill(J.N15);
      }
   }

   SetHistogram(H1_N05, Colors[0]);
   SetHistogram(H2_N05, Colors[1]);
   SetHistogram(H1_N10, Colors[0]);
   SetHistogram(H2_N10, Colors[1]);
   SetHistogram(H1_N15, Colors[0]);
   SetHistogram(H2_N15, Colors[1]);

   AddComparisonPlot(PdfFile, H1_N05, H2_N05);
   AddComparisonPlot(PdfFile, H1_N10, H2_N10);
   AddComparisonPlot(PdfFile, H1_N15, H2_N15);
}

void SetHistogram(TH1D &H, int Color)
{
   H.Scale(1 / H.Integral());
   H.SetLineWidth(2);
   H.SetLineColor(Color);
   H.SetMarkerColor(Color);
   H.SetStats(0);
}

void AddComparisonPlot(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   TLegend Legend(0.2, 0.2, 0.5, 0.35);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "Variation", "pl");
   Legend.AddEntry(&H2, "Pythia6", "pl");

   TCanvas Canvas;

   H1.Draw();
   H2.Draw("same");
   Legend.Draw();
   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);

   static int Index = 0;
   Index = Index + 1;
   TH1D *HR = (TH1D *)H1.Clone(Form("HR%d", Index));
   HR->Divide(&H2);

   HR->GetYaxis()->SetTitle("Ratio");

   HR->Draw();
   Canvas.SetLogy(false);
   HR->SetMinimum(0);
   HR->SetMaximum(2);

   PdfFile.AddCanvas(Canvas);
}
