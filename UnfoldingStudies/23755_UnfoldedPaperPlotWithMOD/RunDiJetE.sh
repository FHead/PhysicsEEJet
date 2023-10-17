#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen

# DiJet E
# ./Execute --Input Input/DataLeadingDiJetENominal.root \
#    --Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetE.${Format} \
#    --RootOutput Root/DataLeadingDiJetENominal.root \
#    --MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/${PYQUEN}LeadingDiJetE.root \
#    --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
#    --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
#    --PrimaryName HUnfoldedBayes7 \
#    --DoSelfNormalize false --DoEventNormalize true \
#    --GenPrimaryMin 0 --GenPrimaryMax 46 \
#    --WorldXMin 20 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
#    --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
#    --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
#    --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
#    --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
#    --IgnoreGroup 0 --Row 1 --Column 1 \
#    --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# DiJet E: log
# ./Execute --Input Input/DataLeadingDiJetENominal.root \
# 	--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetELog.${Format} \
#  --RootOutput Root/DataLeadingDiJetENominal.root \
# 	--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/${PYQUEN}LeadingDiJetE.root \
# 	--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
# 	--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
# 	--PrimaryName HUnfoldedBayes7 \
# 	--DoSelfNormalize false --DoEventNormalize true \
# 	--GenPrimaryMin 0 --GenPrimaryMax 46 \
# 	--WorldXMin 20 --WorldXMax 46 --WorldYMin 0.000000004 --WorldYMax 6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
# 	--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
# 	--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
# 	--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
# 	--Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
# 	--IgnoreGroup 0 --Row 1 --Column 1 \
# 	--DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# DiJet E Corr
./Execute --Input Input/DataLeadingDiJetENominal.root \
   --Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrected.${Format} \
   --RootOutput Root/DataLeadingDiJetENominalCorrected.root \
   --MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/${PYQUEN}LeadingDiJetE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 20 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading Dijet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetJetE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetE \
   --MCCorrection true,true,true,true,true \
   --MCStep1Correction true,false,false,false,false,false \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

./Execute --Input Input/DataLeadingDiJetENominal.root \
   --Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrectedPythia.${Format} \
   --RootOutput Root/DataLeadingDiJetENominalCorrectedPythia.root \
   --MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCVincia1LeadingDiJetE.root",OriginalInput/MCVincia2LeadingDiJetE.root,"OriginalInput/MCPythia8TrueLeadingDiJetE.root","Input/FakeDataLeadingDiJetENominal.root" \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen,HUnfoldedBayes7 \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","P8 Leading","Fake data" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 20 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Leading Dijet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetJetE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetE \
   --MCCorrection true,true,true,true,false,true \
   --MCStep1Correction true,false,false,false,false,true \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
   
# Felix comparison
./Execute --Input Input/DataLeadingDiJetENominal.root \
   --Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrectedFelix.${Format} \
   --RootOutput Root/DataLeadingDiJetENominalCorrectedFelix.root \
   --MCFile "Input/DataLeadingDiJetENominal.root","FelixInput/Graph_2jet.root" \
   --MCHistogram HMCTruth,GFelix \
   --MCLabel "PYTHIA 6","NLL' resummed" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 20 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading Dijet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetJetE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetE \
   --MCCorrection true,false \
   --MCStep1Correction true,false \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
   
./Execute --Input Input/DataLeadingDiJetENominal.root \
   --Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrectedLog.pdf --FinalOutput Plots/MeowLeadingDiJetECorrectedFelixLog.${Format} \
   --RootOutput Root/DataLeadingDiJetENominalCorrectedFelixLog.root \
   --MCFile "Input/DataLeadingDiJetENominal.root","FelixInput/Graph_2jet.root" \
   --MCHistogram HMCTruth,GFelix \
   --MCLabel "PYTHIA 6","NLL' resummed" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 20 --WorldXMax 46 --WorldYMin 0.0015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Leading Dijet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.45 --LegendY 0.15 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetJetE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetE \
   --MCCorrection true,false \
   --MCStep1Correction true,false \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

./Execute --Input Input/DataLeadingDiJetENominal.root \
   --Systematic None --Output Plots/DataLeadingDiJetEReco.pdf --FinalOutput Plots/MeowLeadingDiJetEReco.${Format} \
   --RootOutput Root/DataLeadingDiJetEReco.root \
   --MCFile "Input/DataLeadingDiJetENominal.root" \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize false --DoEventNormalize true \
   --DoReco true \
   --GenPrimaryMin 0 --GenPrimaryMax 84 \
   --RecoPrimaryMin 0 --RecoPrimaryMax 84 \
   --WorldXMin 20 --WorldXMax 84 --WorldYMin 0 --WorldYMax 0.16 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading Dijet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetJetE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetE \
   --MCCorrection true \
   --MCStep1Correction true \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

