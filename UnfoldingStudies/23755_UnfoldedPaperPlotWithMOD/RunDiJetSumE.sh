#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen


# DiJet SumE
# ./Execute --Input Input/DataLeadingDiJetSumENominal.root \
# 	--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumE.${Format} \
#  --RootOutput Root/DataLeadingDiJetSumENominal.root \
# 	--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/${PYQUEN}LeadingDiJetSumE.root \
# 	--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
# 	--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
# 	--PrimaryName HUnfoldedBayes15 \
# 	--DoSelfNormalize false --DoEventNormalize true \
# 	--GenPrimaryMin 0 --GenPrimaryMax 92 \
# 	--WorldXMin 40 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.12 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
# 	--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)  (GeV^{-1})" --Binning "None" \
# 	--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
# 	--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
# 	--Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
# 	--IgnoreGroup 0 --Row 1 --Column 1 \
# 	--DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# DiJet SumE: log
# ./Execute --Input Input/DataLeadingDiJetSumENominal.root \
# 	--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumELog.${Format} \
#  --RootOutput Root/DataLeadingDiJetSumENominal.root \
# 	--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/${PYQUEN}LeadingDiJetSumE.root \
# 	--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
# 	--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
# 	--PrimaryName HUnfoldedBayes16 \
# 	--DoSelfNormalize false --DoEventNormalize true \
# 	--GenPrimaryMin 0 --GenPrimaryMax 92 \
# 	--WorldXMin 40 --WorldXMax 92 --WorldYMin 0.000000004 --WorldYMax 0.6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
# 	--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)  (GeV^{-1})" --Binning "None" \
# 	--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
# 	--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
# 	--Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
# 	--IgnoreGroup 0 --Row 1 --Column 1 \
# 	--DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# DiJet SumE corrected
./Execute --Input Input/DataLeadingDiJetSumENominal.root \
   --Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrected.${Format} \
   --RootOutput Root/DataLeadingDiJetSumENominalCorrected.root \
   --MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/${PYQUEN}LeadingDiJetSumE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes15 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 92 \
   --WorldXMin 40 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.10 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetSumE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetSumE \
   --MCCorrection true,true,true,true,true \
   --MCStep1Correction true,false,false,false,false \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
   
# DiJet SumE, pythia different showers
./Execute --Input Input/DataLeadingDiJetSumENominal.root \
   --Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrectedPythia.${Format} \
   --RootOutput Root/DataLeadingDiJetSumENominalCorrectedPythia.root \
   --MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCVincia1LeadingDiJetSumE.root",OriginalInput/MCVincia2LeadingDiJetSumE.root,OriginalInput/MCPythia8TrueLeadingDiJetSumE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","P8 Leading" \
   --PrimaryName HUnfoldedBayes15 \
   --DoSelfNormalize false --DoEventNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 92 \
   --WorldXMin 40 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.10 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetSumE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetSumE \
   --MCCorrection true,true,true,true,false \
   --MCStep1Correction true,false,false,false,false \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12


./Execute --Input Input/DataLeadingDiJetSumENominal.root \
   --Systematic None --Output Plots/DataLeadingDiJetSumERecoCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumERecoCorrected.${Format} \
   --RootOutput Root/DataLeadingDiJetSumEReco.root \
   --MCFile "Input/DataLeadingDiJetSumENominal.root" \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize false --DoEventNormalize true \
   --DoReco true \
   --GenPrimaryMin 0 --GenPrimaryMax 150 \
   --WorldXMin 40 --WorldXMax 150 --WorldYMin 0 --WorldYMax 0.08 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --CorrectionFile Correction.dh --CorrectionState DijetSumE \
   --Step1CorrectionFile Step1Correction.dh --Step1CorrectionState LeadingDiJetSumE \
   --MCCorrection true \
   --MCStep1Correction true \
   --DoMOD ${DoMOD} --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12



