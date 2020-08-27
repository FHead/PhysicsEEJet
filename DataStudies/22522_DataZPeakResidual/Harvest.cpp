#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TF1.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void SetParameter(TF1 &F, DataHelper &DHFile, int N, double X, int Order);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile", "FitResult.dh");
   string PdfFileName = CL.Get("PdfFile", "ScanResult.pdf");

   DataHelper DHFile(DHFileName);

   TF1 F230("F230", "pol0", 5, 50);
   TF1 F330("F330", "pol0", 5, 50);
   TF1 F430("F430", "pol0", 5, 50);
   TF1 F530("F530", "pol0", 5, 50);
   TF1 F250("F250", "pol0", 5, 50);
   TF1 F350("F350", "pol0", 5, 50);
   TF1 F450("F450", "pol0", 5, 50);
   TF1 F550("F550", "pol0", 5, 50);
   TF1 F360("F360", "pol0", 5, 50);
   TF1 F370("F370", "pol0", 5, 50);
   TF1 F380("F380", "pol0", 5, 50);
   TF1 F390("F390", "pol0", 5, 50);
   TF1 F3100("F3100", "pol0", 5, 50);
   TF1 F460("F460", "pol0", 5, 50);
   TF1 F470("F470", "pol0", 5, 50);
   TF1 F480("F480", "pol0", 5, 50);
   TF1 F490("F490", "pol0", 5, 50);
   TF1 F4100("F4100", "pol0", 5, 50);
   TF1 F930("F930", "pol0", 5, 50);
   TF1 F950("F950", "pol0", 5, 50);
   TF1 F960("F960", "pol0", 5, 50);
   TF1 F980("F980", "pol0", 5, 50);
   TF1 F9100("F9100", "pol0", 5, 50);
   
   TF1 F231("F231", "pol1", 5, 50);
   TF1 F331("F331", "pol1", 5, 50);
   TF1 F431("F431", "pol1", 5, 50);
   TF1 F531("F531", "pol1", 5, 50);
   TF1 F251("F251", "pol1", 5, 50);
   TF1 F351("F351", "pol1", 5, 50);
   TF1 F451("F451", "pol1", 5, 50);
   TF1 F551("F551", "pol1", 5, 50);
   TF1 F361("F361", "pol1", 5, 50);
   TF1 F371("F371", "pol1", 5, 50);
   TF1 F381("F381", "pol1", 5, 50);
   TF1 F391("F391", "pol1", 5, 50);
   TF1 F3101("F3101", "pol1", 5, 50);
   TF1 F461("F461", "pol1", 5, 50);
   TF1 F471("F471", "pol1", 5, 50);
   TF1 F481("F481", "pol1", 5, 50);
   TF1 F491("F491", "pol1", 5, 50);
   TF1 F4101("F4101", "pol1", 5, 50);
   TF1 F931("F931", "pol1", 5, 50);
   TF1 F951("F951", "pol1", 5, 50);
   TF1 F961("F961", "pol1", 5, 50);
   TF1 F981("F981", "pol1", 5, 50);
   TF1 F9101("F9101", "pol1", 5, 50);
   
   TF1 F232("F232", "pol2", 5, 50);
   TF1 F332("F332", "pol2", 5, 50);
   TF1 F432("F432", "pol2", 5, 50);
   TF1 F532("F532", "pol2", 5, 50);
   TF1 F252("F252", "pol2", 5, 50);
   TF1 F352("F352", "pol2", 5, 50);
   TF1 F452("F452", "pol2", 5, 50);
   TF1 F552("F552", "pol2", 5, 50);
   TF1 F362("F362", "pol2", 5, 50);
   TF1 F372("F372", "pol2", 5, 50);
   TF1 F382("F382", "pol2", 5, 50);
   TF1 F392("F392", "pol2", 5, 50);
   TF1 F3102("F3102", "pol2", 5, 50);
   TF1 F462("F462", "pol2", 5, 50);
   TF1 F472("F472", "pol2", 5, 50);
   TF1 F482("F482", "pol2", 5, 50);
   TF1 F492("F492", "pol2", 5, 50);
   TF1 F4102("F4102", "pol2", 5, 50);
   TF1 F932("F932", "pol2", 5, 50);
   TF1 F952("F952", "pol2", 5, 50);
   TF1 F962("F962", "pol2", 5, 50);
   TF1 F982("F982", "pol2", 5, 50);
   TF1 F9102("F9102", "pol2", 5, 50);
   
   TF1 F233("F233", "pol3", 5, 50);
   TF1 F333("F333", "pol3", 5, 50);
   TF1 F433("F433", "pol3", 5, 50);
   TF1 F533("F533", "pol3", 5, 50);
   TF1 F253("F253", "pol3", 5, 50);
   TF1 F353("F353", "pol3", 5, 50);
   TF1 F453("F453", "pol3", 5, 50);
   TF1 F553("F553", "pol3", 5, 50);
   TF1 F363("F363", "pol3", 5, 50);
   TF1 F373("F373", "pol3", 5, 50);
   TF1 F383("F383", "pol3", 5, 50);
   TF1 F393("F393", "pol3", 5, 50);
   TF1 F3103("F3103", "pol3", 5, 50);
   TF1 F463("F463", "pol3", 5, 50);
   TF1 F473("F473", "pol3", 5, 50);
   TF1 F483("F483", "pol3", 5, 50);
   TF1 F493("F493", "pol3", 5, 50);
   TF1 F4103("F4103", "pol3", 5, 50);
   TF1 F933("F933", "pol3", 5, 50);
   TF1 F953("F953", "pol3", 5, 50);
   TF1 F963("F963", "pol3", 5, 50);
   TF1 F983("F983", "pol3", 5, 50);
   TF1 F9103("F9103", "pol3", 5, 50);

   SetParameter(F230, DHFile, 2, 3, 0);
   SetParameter(F330, DHFile, 3, 3, 0);
   SetParameter(F430, DHFile, 4, 3, 0);
   SetParameter(F530, DHFile, 5, 3, 0);
   SetParameter(F250, DHFile, 2, 5, 0);
   SetParameter(F350, DHFile, 3, 5, 0);
   SetParameter(F450, DHFile, 4, 5, 0);
   SetParameter(F550, DHFile, 5, 5, 0);
   SetParameter(F360, DHFile, 3, 6, 0);
   SetParameter(F370, DHFile, 3, 7, 0);
   SetParameter(F380, DHFile, 3, 8, 0);
   SetParameter(F390, DHFile, 3, 9, 0);
   SetParameter(F3100, DHFile, 3, 10, 0);
   SetParameter(F460, DHFile, 4, 6, 0);
   SetParameter(F470, DHFile, 4, 7, 0);
   SetParameter(F480, DHFile, 4, 8, 0);
   SetParameter(F490, DHFile, 4, 9, 0);
   SetParameter(F4100, DHFile, 4, 10, 0);
   SetParameter(F930, DHFile, 9, 3, 0);
   SetParameter(F950, DHFile, 9, 5, 0);
   SetParameter(F960, DHFile, 9, 6, 0);
   SetParameter(F980, DHFile, 9, 8, 0);
   SetParameter(F9100, DHFile, 9, 10, 0);
   
   SetParameter(F231, DHFile, 2, 3, 1);
   SetParameter(F331, DHFile, 3, 3, 1);
   SetParameter(F431, DHFile, 4, 3, 1);
   SetParameter(F531, DHFile, 5, 3, 1);
   SetParameter(F251, DHFile, 2, 5, 1);
   SetParameter(F351, DHFile, 3, 5, 1);
   SetParameter(F451, DHFile, 4, 5, 1);
   SetParameter(F551, DHFile, 5, 5, 1);
   SetParameter(F361, DHFile, 3, 6, 1);
   SetParameter(F371, DHFile, 3, 7, 1);
   SetParameter(F381, DHFile, 3, 8, 1);
   SetParameter(F391, DHFile, 3, 9, 1);
   SetParameter(F3101, DHFile, 3, 10, 1);
   SetParameter(F461, DHFile, 4, 6, 1);
   SetParameter(F471, DHFile, 4, 7, 1);
   SetParameter(F481, DHFile, 4, 8, 1);
   SetParameter(F491, DHFile, 4, 9, 1);
   SetParameter(F4101, DHFile, 4, 10, 1);
   SetParameter(F931, DHFile, 9, 3, 1);
   SetParameter(F951, DHFile, 9, 5, 1);
   SetParameter(F961, DHFile, 9, 6, 1);
   SetParameter(F981, DHFile, 9, 8, 1);
   SetParameter(F9101, DHFile, 9, 10, 1);
   
   SetParameter(F232, DHFile, 2, 3, 2);
   SetParameter(F332, DHFile, 3, 3, 2);
   SetParameter(F432, DHFile, 4, 3, 2);
   SetParameter(F532, DHFile, 5, 3, 2);
   SetParameter(F252, DHFile, 2, 5, 2);
   SetParameter(F352, DHFile, 3, 5, 2);
   SetParameter(F452, DHFile, 4, 5, 2);
   SetParameter(F552, DHFile, 5, 5, 2);
   SetParameter(F362, DHFile, 3, 6, 2);
   SetParameter(F372, DHFile, 3, 7, 2);
   SetParameter(F382, DHFile, 3, 8, 2);
   SetParameter(F392, DHFile, 3, 9, 2);
   SetParameter(F3102, DHFile, 3, 10, 2);
   SetParameter(F462, DHFile, 4, 6, 2);
   SetParameter(F472, DHFile, 4, 7, 2);
   SetParameter(F482, DHFile, 4, 8, 2);
   SetParameter(F492, DHFile, 4, 9, 2);
   SetParameter(F4102, DHFile, 4, 10, 2);
   SetParameter(F932, DHFile, 9, 3, 2);
   SetParameter(F952, DHFile, 9, 5, 2);
   SetParameter(F962, DHFile, 9, 6, 2);
   SetParameter(F982, DHFile, 9, 8, 2);
   SetParameter(F9102, DHFile, 9, 10, 2);
   
   SetParameter(F233, DHFile, 2, 3, 3);
   SetParameter(F333, DHFile, 3, 3, 3);
   SetParameter(F433, DHFile, 4, 3, 3);
   SetParameter(F533, DHFile, 5, 3, 3);
   SetParameter(F253, DHFile, 2, 5, 3);
   SetParameter(F353, DHFile, 3, 5, 3);
   SetParameter(F453, DHFile, 4, 5, 3);
   SetParameter(F553, DHFile, 5, 5, 3);
   SetParameter(F363, DHFile, 3, 6, 3);
   SetParameter(F373, DHFile, 3, 7, 3);
   SetParameter(F383, DHFile, 3, 8, 3);
   SetParameter(F393, DHFile, 3, 9, 3);
   SetParameter(F3103, DHFile, 3, 10, 3);
   SetParameter(F463, DHFile, 4, 6, 3);
   SetParameter(F473, DHFile, 4, 7, 3);
   SetParameter(F483, DHFile, 4, 8, 3);
   SetParameter(F493, DHFile, 4, 9, 3);
   SetParameter(F4103, DHFile, 4, 10, 3);
   SetParameter(F933, DHFile, 9, 3, 3);
   SetParameter(F953, DHFile, 9, 5, 3);
   SetParameter(F963, DHFile, 9, 6, 3);
   SetParameter(F983, DHFile, 9, 8, 3);
   SetParameter(F9103, DHFile, 9, 10, 3);

   PdfFileHelper PdfFile(PdfFileName);
   PdfFile.AddTextPage("Residual from Z: stability checks");

   F230.SetLineColor(kBlue);
   F330.SetLineColor(kBlack);
   F430.SetLineColor(kGreen + 3);
   F530.SetLineColor(kRed);
   F250.SetLineColor(kBlue);
   F350.SetLineColor(kBlack);
   F450.SetLineColor(kGreen + 3);
   F550.SetLineColor(kRed);
   F360.SetLineColor(kGreen + 3);
   F370.SetLineColor(kRed);
   F380.SetLineColor(kMagenta);
   F390.SetLineColor(kBlue);
   F3100.SetLineColor(kGreen);
   F460.SetLineColor(kYellow + 3);
   F470.SetLineColor(kRed);
   F480.SetLineColor(kMagenta);
   F490.SetLineColor(kBlue);
   F4100.SetLineColor(kGreen);
   F930.SetLineColor(kYellow + 3);
   F950.SetLineColor(kRed);
   F960.SetLineColor(kMagenta);
   F980.SetLineColor(kBlue);
   F9100.SetLineColor(kGreen);

   F231.SetLineColor(kBlue);
   F331.SetLineColor(kBlack);
   F431.SetLineColor(kGreen + 3);
   F531.SetLineColor(kRed);
   F251.SetLineColor(kBlue);
   F351.SetLineColor(kBlack);
   F451.SetLineColor(kGreen + 3);
   F551.SetLineColor(kRed);
   F361.SetLineColor(kGreen + 3);
   F371.SetLineColor(kRed);
   F381.SetLineColor(kMagenta);
   F391.SetLineColor(kBlue);
   F3101.SetLineColor(kGreen);
   F461.SetLineColor(kYellow + 3);
   F471.SetLineColor(kRed);
   F481.SetLineColor(kMagenta);
   F491.SetLineColor(kBlue);
   F4101.SetLineColor(kGreen);
   F931.SetLineColor(kYellow + 3);
   F951.SetLineColor(kRed);
   F961.SetLineColor(kMagenta);
   F981.SetLineColor(kBlue);
   F9101.SetLineColor(kGreen);

   F232.SetLineColor(kBlue);
   F332.SetLineColor(kBlack);
   F432.SetLineColor(kGreen + 3);
   F532.SetLineColor(kRed);
   F252.SetLineColor(kBlue);
   F352.SetLineColor(kBlack);
   F452.SetLineColor(kGreen + 3);
   F552.SetLineColor(kRed);
   F362.SetLineColor(kGreen + 3);
   F372.SetLineColor(kRed);
   F382.SetLineColor(kMagenta);
   F392.SetLineColor(kBlue);
   F3102.SetLineColor(kGreen);
   F462.SetLineColor(kYellow + 3);
   F472.SetLineColor(kRed);
   F482.SetLineColor(kMagenta);
   F492.SetLineColor(kBlue);
   F4102.SetLineColor(kGreen);
   F932.SetLineColor(kYellow + 3);
   F952.SetLineColor(kRed);
   F962.SetLineColor(kMagenta);
   F982.SetLineColor(kBlue);
   F9102.SetLineColor(kGreen);

   F233.SetLineColor(kBlue);
   F333.SetLineColor(kBlack);
   F433.SetLineColor(kGreen + 3);
   F533.SetLineColor(kRed);
   F253.SetLineColor(kBlue);
   F353.SetLineColor(kBlack);
   F453.SetLineColor(kGreen + 3);
   F553.SetLineColor(kRed);
   F363.SetLineColor(kGreen + 3);
   F373.SetLineColor(kRed);
   F383.SetLineColor(kMagenta);
   F393.SetLineColor(kBlue);
   F3103.SetLineColor(kGreen);
   F463.SetLineColor(kYellow + 3);
   F473.SetLineColor(kRed);
   F483.SetLineColor(kMagenta);
   F493.SetLineColor(kBlue);
   F4103.SetLineColor(kGreen);
   F933.SetLineColor(kYellow + 3);
   F953.SetLineColor(kRed);
   F963.SetLineColor(kMagenta);
   F983.SetLineColor(kBlue);
   F9103.SetLineColor(kGreen);

   TLegend Legend1(0.55, 0.15, 0.75, 0.15 + 0.06 * 5);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&F250, "N = 2, X = 5", "l");
   Legend1.AddEntry(&F350, "N = 3, X = 5", "l");
   Legend1.AddEntry(&F450, "N = 4, X = 5", "l");
   Legend1.AddEntry(&F550, "N = 5, X = 5", "l");
   Legend1.AddEntry(&F950, "N = 9, X = 5", "l");
   
   TLegend Legend2(0.55, 0.15, 0.75, 0.15 + 0.06 * 6);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&F350, "N = 3, X = 5", "l");
   Legend2.AddEntry(&F360, "N = 3, X = 6", "l");
   Legend2.AddEntry(&F370, "N = 3, X = 7", "l");
   Legend2.AddEntry(&F380, "N = 3, X = 8", "l");
   Legend2.AddEntry(&F390, "N = 3, X = 9", "l");
   Legend2.AddEntry(&F3100, "N = 3, X = 10", "l");
   
   TLegend Legend3(0.55, 0.15, 0.75, 0.15 + 0.06 * 6);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetFillStyle(0);
   Legend3.SetBorderSize(0);
   Legend3.AddEntry(&F450, "N = 4, X = 5", "l");
   Legend3.AddEntry(&F460, "N = 4, X = 6", "l");
   Legend3.AddEntry(&F470, "N = 4, X = 7", "l");
   Legend3.AddEntry(&F480, "N = 4, X = 8", "l");
   Legend3.AddEntry(&F490, "N = 4, X = 9", "l");
   Legend3.AddEntry(&F4100, "N = 4, X = 10", "l");

   TLegend Legend4(0.55, 0.15, 0.75, 0.15 + 0.06 * 5);
   Legend4.SetTextFont(42);
   Legend4.SetTextSize(0.035);
   Legend4.SetFillStyle(0);
   Legend4.SetBorderSize(0);
   Legend4.AddEntry(&F230, "N = 2, X = 3", "l");
   Legend4.AddEntry(&F330, "N = 3, X = 3", "l");
   Legend4.AddEntry(&F430, "N = 4, X = 3", "l");
   Legend4.AddEntry(&F530, "N = 5, X = 3", "l");
   Legend4.AddEntry(&F930, "N = 9, X = 3", "l");
 
   TLegend Legend5(0.55, 0.15, 0.75, 0.15 + 0.06 * 5);
   Legend5.SetTextFont(42);
   Legend5.SetTextSize(0.035);
   Legend5.SetFillStyle(0);
   Legend5.SetBorderSize(0);
   Legend5.AddEntry(&F930, "N = 9, X = 3", "l");
   Legend5.AddEntry(&F950, "N = 9, X = 5", "l");
   Legend5.AddEntry(&F960, "N = 9, X = 6", "l");
   Legend5.AddEntry(&F980, "N = 9, X = 8", "l");
   Legend5.AddEntry(&F9100, "N = 9, X = 10", "l");

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";Jet P;Correction", 100, 0, 50, 100, 0.975, 1.025);
   HWorld.SetStats(0);

   HWorld.SetTitle("Order = 0");
   HWorld.Draw("axis");
   F250.Draw("same");
   F350.Draw("same");
   F450.Draw("same");
   F550.Draw("same");
   F950.Draw("same");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 1");
   HWorld.Draw("axis");
   F251.Draw("same");
   F351.Draw("same");
   F451.Draw("same");
   F551.Draw("same");
   F951.Draw("same");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 2");
   HWorld.Draw("axis");
   F252.Draw("same");
   F352.Draw("same");
   F452.Draw("same");
   F552.Draw("same");
   F952.Draw("same");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 3");
   HWorld.Draw("axis");
   F253.Draw("same");
   F353.Draw("same");
   F453.Draw("same");
   F553.Draw("same");
   F953.Draw("same");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 0");
   HWorld.Draw("axis");
   F350.Draw("same");
   F360.Draw("same");
   F370.Draw("same");
   F380.Draw("same");
   F390.Draw("same");
   F3100.Draw("same");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 1");
   HWorld.Draw("axis");
   F351.Draw("same");
   F361.Draw("same");
   F371.Draw("same");
   F381.Draw("same");
   F391.Draw("same");
   F3101.Draw("same");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 2");
   HWorld.Draw("axis");
   F352.Draw("same");
   F362.Draw("same");
   F372.Draw("same");
   F382.Draw("same");
   F392.Draw("same");
   F3102.Draw("same");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 3");
   HWorld.Draw("axis");
   F353.Draw("same");
   F363.Draw("same");
   F373.Draw("same");
   F383.Draw("same");
   F393.Draw("same");
   F3103.Draw("same");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 0");
   HWorld.Draw("axis");
   F450.Draw("same");
   F460.Draw("same");
   F470.Draw("same");
   F480.Draw("same");
   F490.Draw("same");
   F4100.Draw("same");
   Legend3.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 1");
   HWorld.Draw("axis");
   F451.Draw("same");
   F461.Draw("same");
   F471.Draw("same");
   F481.Draw("same");
   F491.Draw("same");
   F4101.Draw("same");
   Legend3.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 2");
   HWorld.Draw("axis");
   F452.Draw("same");
   F462.Draw("same");
   F472.Draw("same");
   F482.Draw("same");
   F492.Draw("same");
   F4102.Draw("same");
   Legend3.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 3");
   HWorld.Draw("axis");
   F453.Draw("same");
   F463.Draw("same");
   F473.Draw("same");
   F483.Draw("same");
   F493.Draw("same");
   F4103.Draw("same");
   Legend3.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 0");
   HWorld.Draw("axis");
   F230.Draw("same");
   F330.Draw("same");
   F430.Draw("same");
   F530.Draw("same");
   F930.Draw("same");
   Legend4.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 1");
   HWorld.Draw("axis");
   F231.Draw("same");
   F331.Draw("same");
   F431.Draw("same");
   F531.Draw("same");
   F931.Draw("same");
   Legend4.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 2");
   HWorld.Draw("axis");
   F232.Draw("same");
   F332.Draw("same");
   F432.Draw("same");
   F532.Draw("same");
   F932.Draw("same");
   Legend4.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 3");
   HWorld.Draw("axis");
   F233.Draw("same");
   F333.Draw("same");
   F433.Draw("same");
   F533.Draw("same");
   F933.Draw("same");
   Legend4.Draw();
   PdfFile.AddCanvas(Canvas);
   
   HWorld.SetTitle("Order = 0");
   HWorld.Draw("axis");
   F930.Draw("same");
   F950.Draw("same");
   F960.Draw("same");
   F980.Draw("same");
   F9100.Draw("same");
   Legend5.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 1");
   HWorld.Draw("axis");
   F931.Draw("same");
   F951.Draw("same");
   F961.Draw("same");
   F981.Draw("same");
   F9101.Draw("same");
   Legend5.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 2");
   HWorld.Draw("axis");
   F932.Draw("same");
   F952.Draw("same");
   F962.Draw("same");
   F982.Draw("same");
   F9102.Draw("same");
   Legend5.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("Order = 3");
   HWorld.Draw("axis");
   F933.Draw("same");
   F953.Draw("same");
   F963.Draw("same");
   F983.Draw("same");
   F9103.Draw("same");
   Legend5.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorld.SetTitle("A lot of curves or order 0");
   HWorld.Draw("axis");
   F330.Draw("same");
   F430.Draw("same");
   F530.Draw("same");
   F350.Draw("same");
   F450.Draw("same");
   F550.Draw("same");
   F360.Draw("same");
   F370.Draw("same");
   F380.Draw("same");
   F390.Draw("same");
   F3100.Draw("same");
   F460.Draw("same");
   F470.Draw("same");
   F480.Draw("same");
   F490.Draw("same");
   F4100.Draw("same");
   F930.Draw("same");
   F950.Draw("same");
   F960.Draw("same");
   F980.Draw("same");
   F9100.Draw("same");
   PdfFile.AddCanvas(Canvas);
   
   HWorld.SetTitle("A lot of curves or order 1");
   HWorld.Draw("axis");
   F331.Draw("same");
   F431.Draw("same");
   F531.Draw("same");
   F351.Draw("same");
   F451.Draw("same");
   F551.Draw("same");
   F361.Draw("same");
   F371.Draw("same");
   F381.Draw("same");
   F391.Draw("same");
   F3101.Draw("same");
   F461.Draw("same");
   F471.Draw("same");
   F481.Draw("same");
   F491.Draw("same");
   F4101.Draw("same");
   F931.Draw("same");
   F951.Draw("same");
   F961.Draw("same");
   F981.Draw("same");
   F9101.Draw("same");
   PdfFile.AddCanvas(Canvas);
   
   HWorld.SetTitle("A lot of curves or order 2");
   HWorld.Draw("axis");
   F332.Draw("same");
   F432.Draw("same");
   F532.Draw("same");
   F352.Draw("same");
   F452.Draw("same");
   F552.Draw("same");
   F362.Draw("same");
   F372.Draw("same");
   F382.Draw("same");
   F392.Draw("same");
   F3102.Draw("same");
   F462.Draw("same");
   F472.Draw("same");
   F482.Draw("same");
   F492.Draw("same");
   F4102.Draw("same");
   F932.Draw("same");
   F952.Draw("same");
   F962.Draw("same");
   F982.Draw("same");
   F9102.Draw("same");
   PdfFile.AddCanvas(Canvas);
   
   HWorld.SetTitle("A lot of curves or order 3");
   HWorld.Draw("axis");
   F333.Draw("same");
   F433.Draw("same");
   F533.Draw("same");
   F353.Draw("same");
   F453.Draw("same");
   F553.Draw("same");
   F363.Draw("same");
   F373.Draw("same");
   F383.Draw("same");
   F393.Draw("same");
   F3103.Draw("same");
   F463.Draw("same");
   F473.Draw("same");
   F483.Draw("same");
   F493.Draw("same");
   F4103.Draw("same");
   F933.Draw("same");
   F953.Draw("same");
   F963.Draw("same");
   F983.Draw("same");
   F9103.Draw("same");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void SetParameter(TF1 &F, DataHelper &DHFile, int N, double X, int Order)
{
   string State = Form("Scan_%d_%.0f", N, X);
   for(int i = 0; i <= Order; i++)
      F.SetParameter(i, DHFile[State][Form("P%d%d",Order,i)].GetDouble());
}



