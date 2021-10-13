DoMOD = true
Format = eps
LeadingDiJetScale = 1
# LeadingDiJetScale = 1.5262468673783047
# 1 / 0.655202

default: RunTest

Prepare:
	rm -f OriginalInput Input Systematics JoaoInput FelixInput
	ln -sf ../23411_UnfoldingPreparation/Output OriginalInput
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	ln -sf ../23514_JoaoConversion/ JoaoInput
	ln -sf ../23472_LeadingDiJetStudies/Correction.dh .
	ln -fs ../24113_FelixResult/ FelixInput
	mkdir -p Plots

PYQUEN = MCPyquen
# PYQUEN = MCPyquenStrong

RunTest: RunJetE RunDiJetE RunDiJetSumE RunJetZG RunJetRG RunJetMG RunJetMGE RunJetZG2 RunJetRG2 RunJetM RunJetME RunConversion

RunJetE: Execute
	# Jet E: Count
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/MeowECount.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 722","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 9000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "dN / d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELog.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized - log
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowE.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: pythia variations only
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowEPythia.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCVincia1JetE.root",OriginalInput/MCVincia2JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized, Joao comparison
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELogJoao.$(Format) \
		--MCFile "JoaoInput/GraphsNLO.root","JoaoInput/GraphsNLO.root","Input/DataJetENominal.root" \
		--MCHistogram GSys,GStat,HMCTruth \
		--MCLabel "NLO Scale","NLO Stat","PYTHIA 6" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: normalized, felix comparison
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELogFelix.$(Format) \
		--MCFile "FelixInput/Graph_inclusive.root","Input/DataJetENominal.root" \
		--MCHistogram GFelix,HMCTruth \
		--MCLabel "Felix","PYTHIA 6" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetE: Execute
	# DiJet E
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetE.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet E: log
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetELog.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.000000004 --WorldYMax 6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet E Corr
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrected.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetJetE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrectedPythia.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCVincia1LeadingDiJetE.root",OriginalInput/MCVincia2LeadingDiJetE.root,"OriginalInput/MCPythia8TrueLeadingDiJetE.root","Input/FakeDataLeadingDiJetENominal.root" \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen,HUnfoldedBayes7 \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","P8 Leading","Fake data" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetJetE \
		--MCCorrection true,true,true,true,false,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Felix comparison
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrectedPythia.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","FelixInput/Graph_2jet.root" \
		--MCHistogram HMCTruth,GFelix \
		--MCLabel "PYTHIA 6","Felix" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetJetE \
		--MCCorrection true,false \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetSumE: Execute
	# DiJet SumE
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumE.$(Format) \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.12 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet SumE: log
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumELog.$(Format) \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0.000000004 --WorldYMax 0.6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet SumE corrected
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrected.$(Format) \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.12 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetSumE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet SumE, pythia different showers
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrectedPythia.$(Format) \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCVincia1LeadingDiJetSumE.root",OriginalInput/MCVincia2LeadingDiJetSumE.root,OriginalInput/MCPythia8TrueLeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","P8 Leading" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale $(LeadingDiJetScale) \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.06 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetSumE \
		--MCCorrection true,true,true,true,false \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunJetZG: Execute
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.$(Format) \
		--MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCHerwigJetZG.root",OriginalInput/MCSherpaJetZG.root,OriginalInput/$(PYQUEN)JetZG.root \
		--MCHistogram HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZGPythia.$(Format) \
		--MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCVincia1JetZG.root",OriginalInput/MCVincia2JetZG.root \
		--MCHistogram HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetRG: Execute
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.$(Format) \
		--MCFile "Input/DataJetRGNominal.root","OriginalInput/MCPythia8JetRG.root","OriginalInput/MCHerwigJetRG.root",OriginalInput/MCSherpaJetRG.root,OriginalInput/$(PYQUEN)JetRG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes8 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRGPythia.$(Format) \
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
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetMG: Execute
	./Execute --Input Input/DataJetMGNominal.root \
		--Systematic Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MeowMG.$(Format) \
		--MCFile "Input/DataJetMGNominal.root","OriginalInput/MCPythia8JetMG.root","OriginalInput/MCHerwigJetMG.root",OriginalInput/MCSherpaJetMG.root,OriginalInput/$(PYQUEN)JetMG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 14.999 \
		--WorldXMin -0.1 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.5 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}" --YLabel "1/N dN/d(Jet M_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetMGE: Execute
	./Execute --Input Input/DataJetMGENominal.root \
		--Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGE.$(Format) \
		--MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCHerwigJetMGE.root",OriginalInput/MCSherpaJetMGE.root,OriginalInput/$(PYQUEN)JetMGE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
	./Execute --Input Input/DataJetMGENominal.root \
		--Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGEPythia.$(Format) \
		--MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCVincia1JetMGE.root",OriginalInput/MCVincia2JetMGE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetZG2: Execute
	./Execute --Input Input/DataJetZG2Nominal.root \
		--Systematic None --Output Plots/DataJetZG2Nominal.pdf --FinalOutput Plots/MeowZG2.$(Format) \
		--MCFile "Input/DataJetZG2Nominal.root","OriginalInput/MCPythia8JetZG2.root","OriginalInput/MCHerwigJetZG2.root",OriginalInput/MCSherpaJetZG2.root,OriginalInput/$(PYQUEN)JetZG2.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.015 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.5 #beta = 1.5" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetRG2: Execute
	./Execute --Input Input/DataJetRG2Nominal.root \
		--Systematic None --Output Plots/DataJetRG2Nominal.pdf --FinalOutput Plots/MeowRG2.$(Format) \
		--MCFile "Input/DataJetRG2Nominal.root","OriginalInput/MCPythia8JetRG2.root","OriginalInput/MCHerwigJetRG2.root",OriginalInput/MCSherpaJetRG2.root,OriginalInput/$(PYQUEN)JetRG2.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.5 #beta = 1.5" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetM: Execute
	./Execute --Input Input/DataJetMNominal.root \
		--Systematic Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MeowM.$(Format) \
		--MCFile "Input/DataJetMNominal.root","OriginalInput/MCPythia8JetM.root","OriginalInput/MCHerwigJetM.root",OriginalInput/MCSherpaJetM.root,OriginalInput/$(PYQUEN)JetM.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 14.999 \
		--WorldXMin 0 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.599 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M" --YLabel "1/N dN/d(Jet M)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
	./Execute --Input Input/DataJetMNominal.root \
		--Systematic Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MeowMPythia.$(Format) \
		--MCFile "Input/DataJetMNominal.root","OriginalInput/MCPythia8JetM.root","OriginalInput/MCVincia1JetM.root",OriginalInput/MCVincia2JetM.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 14.999 \
		--WorldXMin 0 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.599 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M" --YLabel "1/N dN/d(Jet M)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetME: Execute
	./Execute --Input Input/DataJetMENominal.root \
		--Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowME.$(Format) \
		--MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root","OriginalInput/MCHerwigJetME.root",OriginalInput/MCSherpaJetME.root,OriginalInput/$(PYQUEN)JetME.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
	./Execute --Input Input/DataJetMENominal.root \
		--Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowMEPythia.$(Format) \
		--MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root","OriginalInput/MCVincia1JetME.root",OriginalInput/MCVincia2JetME.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
