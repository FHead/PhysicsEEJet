#include <vector>
#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void Transcribe(DataHelper &DHFile, string State, TGraphAsymmErrors &G, double Offset);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName     = CL.Get("DHFile");
   string OutputFileName = CL.Get("Output");
   
   DataHelper DHFile(DHFileName);

   vector<string> States = CL.GetStringVector("States");
   vector<int> Colors    = CL.GetIntVector("Colors");
   vector<string> Labels = CL.GetStringVector("Labels");

   double XMin           = CL.GetDouble("XMin", 0.500);
   double XMax           = CL.GetDouble("XMax", 0.800);
   double YMin           = CL.GetDouble("YMin", 0.994);
   double YMax           = CL.GetDouble("YMax", 1.003);

   int N = States.size();

   vector<TGraphAsymmErrors> G(N);
   for(int i = 0; i < N; i++)
   {
      Transcribe(DHFile, States[i], G[i], i * 0.0005);
      G[i].SetLineColor(Colors[i]);
      G[i].SetMarkerColor(Colors[i]);
      G[i].SetMarkerStyle(20);
   }

   TCanvas Canvas;

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 1, 1);

   TH2D HWorld("HWorld", ";#theta(#pi);<P+>/<P->", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   for(int i = 0; i < N; i++)
      G[i].Draw("p");
   GLine.Draw("l");

   TLegend Legend(0.45, 0.85, 0.75, 0.65);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&G[i], Labels[i].c_str(), "pl");
   Legend.Draw();

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}

void Transcribe(DataHelper &DHFile, string State, TGraphAsymmErrors &G, double Offset)
{
   int N = DHFile[State]["NBins"].GetInteger();

   for(int i = 0; i < N; i++)
   {
      double XMin   = DHFile[State][Form("B%dMin",i)].GetDouble();
      double XMax   = DHFile[State][Form("B%dMax",i)].GetDouble();
      double Y      = DHFile[State][Form("B%dPMR",i)].GetDouble();
      double YError = DHFile[State][Form("B%dPME",i)].GetDouble();

      double X = (XMin + XMax) / 2 + Offset;
      double EXL = X - XMin;
      double EXH = XMax - X;

      G.SetPoint(i, X, Y);
      G.SetPointError(i, EXL, EXH, YError, YError);
   }
}



