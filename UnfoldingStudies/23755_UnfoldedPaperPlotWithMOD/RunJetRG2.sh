#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen

./Execute --Input Input/DataJetRG2Nominal.root \
   --Systematic None --Output Plots/DataJetRG2Nominal.pdf --FinalOutput Plots/MeowRG2.${Format} \
   --MCFile "Input/DataJetRG2Nominal.root","OriginalInput/MCPythia8JetRG2.root","OriginalInput/MCHerwigJetRG2.root",OriginalInput/MCSherpaJetRG2.root,OriginalInput/${PYQUEN}JetRG2.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes14 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
   --WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.5 #beta = 1.5" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

