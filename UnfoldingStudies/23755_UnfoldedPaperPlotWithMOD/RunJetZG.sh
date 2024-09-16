#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen

./Execute --Input Input/DataJetZGNominal.root --Systematic Systematics/DataJetZGNormalized.root \
   --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.${Format} \
   --RootOutput Root/DataJetZGNominal.root \
   --MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCHerwigJetZG.root",OriginalInput/MCSherpaJetZG.root,OriginalInput/${PYQUEN}JetZG.root \
   --MCHistogram HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetZGNominal.root \
   --Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZGPythia.${Format} \
   --RootOutput Root/DataJetZGNominalPythia.root \
   --MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCVincia1JetZG.root",OriginalInput/MCVincia2JetZG.root,OriginalInput/MCJetScapeJetZG.root \
   --MCHistogram HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","JetScape" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetZGNominal.root \
   --Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZGJetScape.${Format} \
   --RootOutput Root/DataJetZGNominalPythia.root \
   --MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root",OriginalInput/MCJetScapeJetZG.root,OriginalInput/MCJetScapeBypassJetZG.root,OriginalInput/MCJetScapeSmashJetZG.root,OriginalInput/MCJetScapeLHEJetZG.root \
   --MCHistogram HMCGen,HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","JS Matter","JS FSR","JS Matter+Smash","JS Madgraph" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetZGNominal.root \
   --Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGGenReweight.pdf --FinalOutput Plots/MeowZGGenReweight.${Format} \
   --RootOutput Root/DataJetZGNominalGenReweight.root \
   --MCFile "Input/DataJetZGGenReweightN05Test.root","Input/DataJetZGGenReweightN10Test.root","Input/DataJetZGGenReweightN15Test.root","Input/DataJetZGGenReweightZGDown.root","Input/DataJetZGGenReweightZGUp.root","Input/DataJetZGGenReweightRGDown.root","Input/DataJetZGGenReweightRGUp.root" \
   --MCHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
   --MCLabel "N05Test","N10Test","N15Test","ZGDown","ZGUp","RGDown","RGUp" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetZGNominal.root \
   --Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGSJSmear.pdf --FinalOutput Plots/MeowZGSJSmear.${Format} \
   --RootOutput Root/DataJetZGNominalSJSmear.root \
   --MCFile "Input/DataJetZGSJSmear.root" \
   --MCHistogram HUnfoldedBayes17 \
   --MCLabel "SJSmear" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.94 --WorldRMax 1.05 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08


./Execute --Input Input/DataJetZGNominal.root --Systematic None \
   --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZGReco.${Format} \
   --RootOutput Root/DataJetZGReco.root \
   --MCFile Input/DataJetZGNominal.root \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize true \
   --DoReco true \
   --GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
   --RecoPrimaryMin -0.01 --RecoPrimaryMax 0.5 \
   --WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
   --XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 3 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08


