DoMOD = true
Group = --Group 2,8 --Row 1 --Column 2

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

Deploy:
	mkdir -p ../FinalResult/SystematicsPartial
	cp Plots/*png ../FinalResult/SystematicsPartial

RunTest: RunJetZG RunJetRG RunJetMG RunJetMGE RunJetM RunJetME RunConversion
# RunTest: RunJetE RunJetZG RunConversion

RunJetE: Execute
	./Execute --Input Systematics/DataJetE.root \
		--Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/SystematicsP.eps \
		--GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "Fractional Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"$(Preliminary)",0,0.1,0.85,"Anti-k_{T} jet R = 0.4" \
		--Group 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HReweight \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Model" \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.8 --LogoY 0.8 --LogoW 0.12

RunDiJetE: Execute
	./Execute --Input Systematics/DataLeadingDiJetE.root \
		--Output Plots/DataLeadingDiJetENominalCount.pdf --FinalOutput Plots/SystematicsLeadingDiJet.eps \
		--GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.55 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "Fractional Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"$(Preliminary)",0,0.65,0.85,"Anti-k_{T} jet R = 0.4",0,0.65,0.8,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HLowSumE,HHighSumE,HSmearSumE,HCorrectionFit,HCorrectionMC,HRecoGenCut,HReweight \
		--SystematicGroups 1,1,2,2,0,3,3,4,5,6,7,7,7,7,7,7,8 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Selection","Model" \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.75 --LogoY 0.65 --LogoW 0.12

RunDiJetSumE: Execute
	./Execute --Input Systematics/DataLeadingDiJetSumE.root \
		--Output Plots/DataLeadingDiJetSumENominalCount.pdf --FinalOutput Plots/SystematicsLeadingDiJetSum.eps \
		--GenPrimaryMax 92 \
		--WorldXMin 20 --WorldXMax 92 --WorldYMin 0 --WorldYMax 1.05 --LogY false \
		--XLabel "Leading dijet Sum E (GeV)" --YLabel "Fractional Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"$(Preliminary)",0,0.65,0.85,"Anti-k_{T} jet R = 0.4",0,0.65,0.8,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HLowSumE,HHighSumE,HSmearSumE,HCorrectionFit,HCorrectionMC,HRecoGenCut,HReweight \
		--SystematicGroups 1,1,2,2,0,3,3,4,5,6,7,7,7,7,7,7,8 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Selection","Model" \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.75 --LogoY 0.65 --LogoW 0.12

RunJetZG: Execute
	./Execute --Input Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/PartialSystematicsZG.eps \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.23 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.35 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HReweight,HSJSmear \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6,7,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Model" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunJetRG: Execute
	./Execute --Input Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/PartialSystematicsRG.eps \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.3 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HReweight,HSJSmear \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6,7,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Model" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunJetMG: Execute
	./Execute --Input Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/PartialSystematicsMG.eps \
		--GenPrimaryMin -0.1 --GenPrimaryMax 15 \
		--WorldXMin -0.1 --WorldXMax 15 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet M_{G}" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunJetMGE: Execute
	./Execute --Input Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/PartialSystematicsMGE.eps \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 0.6 --LogY false \
		--XLabel "Jet M_{G} / E" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HReweight,HSJSmear \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6,7,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Model" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunJetM: Execute
	./Execute --Input Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/PartialSystematicsM.eps \
		--GenPrimaryMin 0 --GenPrimaryMax 15 \
		--WorldXMin 0 --WorldXMax 15 --WorldYMin 0 --WorldYMax 0.749 --LogY false \
		--XLabel "Jet M" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunJetME: Execute
	./Execute --Input Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/PartialSystematicsME.eps \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 0.749 --LogY false \
		--XLabel "Jet M/E" --YLabel "Fractional Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.07 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts 0,0.3,0.65,"$(Preliminary)",0,0.3,0.55,"Anti-k_{T} jet R = 0.4" \
		$(Group) \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HReweight,HSJSmear \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6,7,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Model" \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.90 --LogoY 0.96 --LogoW 0.1

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

