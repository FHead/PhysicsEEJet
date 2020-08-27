#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH2D.h"

#include "Code/DrawRandom.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TGraph GA;

   TH1D SA("SA", ";Jet sigma;A sigma", 25, 0, 0.25);

   for(double S = 0.01; S < 0.25; S = S + 0.01)
   {
      TH1D HP("HP", ";;", 100, 0, 100);
      TH1D HM("HM", ";;", 100, 0, 100);
      TH1D HA("HA", ";;", 100, -2, 2);

      for(int i = 0; i < 1000000; i++)
      {
         double P = 45 * DrawGaussian(1, S);
         double M = 45 * DrawGaussian(1, S);

         HP.Fill(P);
         HM.Fill(M);
         HA.Fill((P - M) / (P + M));
      }

      int N = GA.GetN();
      GA.SetPoint(N, S, HA.GetRMS());
   }

   PdfFileHelper PdfFile("Toy.pdf");

   TF1 F("F", "[0]*x+[1]*x*x", 0, 0.25);

   GA.GetXaxis()->SetRangeUser(0, 0.25);
   GA.GetYaxis()->SetRangeUser(0, 0.20);
   GA.Fit(&F, "0");

   TH2D HWorld("HWorld", ";Jet;Asym", 100, 0, 0.25, 100, 0, 0.20);
   HWorld.SetStats(0);

   TCanvas Canvas;
   
   HWorld.Draw("axis");
   GA.Draw("pl");
   F.Draw("same");

   PdfFile.AddCanvas(Canvas);

   PdfFile.Close();

   return 0;
}




