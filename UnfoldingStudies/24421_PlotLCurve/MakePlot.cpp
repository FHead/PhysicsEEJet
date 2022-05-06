#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("OutputBase");

   string LCurveName = CL.Get("Curve", "GTUnfoldLCurve");
   string XYName = CL.Get("XY", "GTUnfoldXY");
   string CurvatureName = CL.Get("Curvature", "STUnfoldTauCurvature");
   string XTName = CL.Get("XT", "GTUnfoldXT");

   TFile File(InputFileName.c_str());

   TCanvas Canvas;

   TGraph *Graph = (TGraph *)File.Get(LCurveName.c_str());
   TGraph *XY = (TGraph *)File.Get(XYName.c_str());
   TSpline *CGraph = (TSpline *)File.Get(CurvatureName.c_str());
   TGraph *XT = (TGraph *)File.Get(XTName.c_str());

   Graph->SetLineWidth(2);
   Graph->SetLineColor(kBlue);
   XY->SetMarkerStyle(20);
   XY->SetMarkerColor(kBlack);
   XY->SetMarkerSize(2);

   Graph->SetTitle("");
   Graph->GetXaxis()->SetTitle("log_{10}#chi^{2}_{A}");
   Graph->GetYaxis()->SetTitle("log_{10}#chi^{2}_{L}");

   Graph->Draw("al");
   XY->Draw("p");

   Canvas.SaveAs((OutputFileName + "_LCurve.pdf").c_str());
   
   CGraph->SetLineWidth(2);
   CGraph->SetLineColor(kBlue);

   double Tau = XT->GetPointY(0);
   TGraph GT;
   GT.SetPoint(0, Tau, -1000);
   GT.SetPoint(1, Tau, +1000);
   
   CGraph->SetTitle(";#tau;curvature");

   CGraph->Draw("C");
   GT.Draw("l");

   Canvas.SaveAs((OutputFileName + "_Curvature.pdf").c_str());

   File.Close();

   return 0;
}



