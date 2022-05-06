#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen



./Execute --Input Input/DataJetRGNominal.root \
   --Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.${Format} \
   --RootOutput Root/DataJetRGNominal.root \
   --MCFile "Input/DataJetRGNominal.root","OriginalInput/MCPythia8JetRG.root","OriginalInput/MCHerwigJetRG.root",OriginalInput/MCSherpaJetRG.root,OriginalInput/${PYQUEN}JetRG.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes8 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetRGNominal.root \
   --Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRGPythia.${Format} \
   --RootOutput Root/DataJetRGNominalPythia.root \
   --MCFile "Input/DataJetRGNominal.root","OriginalInput/MCPythia8JetRG.root","OriginalInput/MCVincia1JetRG.root",OriginalInput/MCVincia2JetRG.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
   --PrimaryName HUnfoldedBayes8 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetRGNominal.root \
   --Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGGenReweight.pdf --FinalOutput Plots/MeowRGGenReweight.${Format} \
   --RootOutput Root/DataJetRGGenReweight.root \
   --MCFile "Input/DataJetRGGenReweightN05Test.root","Input/DataJetRGGenReweightN10Test.root","Input/DataJetRGGenReweightN15Test.root","Input/DataJetRGGenReweightZGDown.root","Input/DataJetRGGenReweightZGUp.root","Input/DataJetRGGenReweightRGDown.root","Input/DataJetRGGenReweightRGUp.root" \
   --MCHistogram HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8 \
   --MCLabel "N05Test","N10Test","N15Test","ZGDown","ZGUp","RGDown","RGUp" \
   --PrimaryName HUnfoldedBayes8 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetRGNominal.root \
   --Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGSJSmear.pdf --FinalOutput Plots/MeowRGSJSmear.${Format} \
   --RootOutput Root/DataJetRGSJSmear.root \
   --MCFile "Input/DataJetRGSJSmear.root" \
   --MCHistogram HUnfoldedBayes8 \
   --MCLabel "SJSmear" \
   --PrimaryName HUnfoldedBayes8 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.89 --WorldRMax 1.14 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetRGNominal.root \
   --Systematic None --Output Plots/DataJetRGReco.pdf --FinalOutput Plots/MeowRGReco.${Format} \
   --RootOutput Root/DataJetRGReco.root \
   --MCFile "Input/DataJetRGNominal.root" \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize true \
   --DoReco true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --RecoPrimaryMin -0.015 --RecoPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 3 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08


