#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen


./Execute --Input Input/DataJetMGENominal.root \
   --Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGE.${Format} \
   --RootOutput Root/DataJetMGENominal.root \
   --MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCHerwigJetMGE.root",OriginalInput/MCSherpaJetMGE.root,OriginalInput/${PYQUEN}JetMGE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes16 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
   
./Execute --Input Input/DataJetMGENominal.root \
   --Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGEPythia.${Format} \
   --RootOutput Root/DataJetMGENominalPythia.root \
   --MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCVincia1JetMGE.root",OriginalInput/MCVincia2JetMGE.root,Input/DataJetMGETighter.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HUnfoldedBayes16 \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","Tighter global cut" \
   --PrimaryName HUnfoldedBayes16 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetMGENominal.root \
   --Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGEGenReweight.pdf --FinalOutput Plots/MeowMGEGenReweight.${Format} \
   --RootOutput Root/DataJetMGENominalGenReweight.root \
   --MCFile "Input/DataJetMGEGenReweightN05Test.root","Input/DataJetMGEGenReweightN10Test.root","Input/DataJetMGEGenReweightN15Test.root","Input/DataJetMGEGenReweightZGDown.root","Input/DataJetMGEGenReweightZGUp.root","Input/DataJetMGEGenReweightRGDown.root","Input/DataJetMGEGenReweightRGUp.root" \
   --MCHistogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
   --MCLabel "N05Test","N10Test","N15Test","ZGDown","ZGUp","RGDown","RGUp" \
   --PrimaryName HUnfoldedBayes16 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetMGENominal.root \
   --Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGESJSmear.pdf --FinalOutput Plots/MeowMGESJSmear.${Format} \
   --RootOutput Root/DataJetMGENominalSJSmear.root \
   --MCFile "Input/DataJetMGESJSmear.root" \
   --MCHistogram HUnfoldedBayes16 \
   --MCLabel "SJSmear" \
   --PrimaryName HUnfoldedBayes16 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.89 --WorldRMax 1.14 --LogY false \
   --XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetMGENominal.root \
   --Systematic None --Output Plots/DataJetMGEReco.pdf --FinalOutput Plots/MeowMGEReco.${Format} \
   --RootOutput Root/DataJetMGEReco.root \
   --MCFile "Input/DataJetMGENominal.root" \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize true \
   --DoReco true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --RecoPrimaryMin -0.01 --RecoPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 3 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
