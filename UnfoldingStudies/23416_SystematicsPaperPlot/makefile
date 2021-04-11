Format = pdf

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

RunTest: Execute
	./Execute --Input Systematics/DataJetE.root \
		--Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/SystematicsP.$(Format) \
		--GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake"
	./Execute --Input Systematics/DataLeadingDiJetE.root \
		--Output Plots/DataLeadingDiJetENominalCount.pdf --FinalOutput Plots/SystematicsLeadingDiJet.$(Format) \
		--GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.55 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Preliminary",0,0.65,0.85,"Anti-k_{T} jet R = 0.4",0,0.65,0.8,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HSumE \
		--SystematicGroups 1,1,2,2,0,3,3,4,5,6,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Selection"
	./Execute --Input Systematics/DataLeadingDiJetSumE.root \
		--Output Plots/DataLeadingDiJetSumENominalCount.pdf --FinalOutput Plots/SystematicsLeadingDiJetSum.$(Format) \
		--GenPrimaryMax 92 \
		--WorldXMin 20 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.75 --LogY false \
		--XLabel "Leading dijet Sum E (GeV)" --YLabel "Uncertainty" --Binning "None" \
		--LegendX 0.4 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Preliminary",0,0.65,0.85,"Anti-k_{T} jet R = 0.4",0,0.65,0.8,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HSumE \
		--SystematicGroups 1,1,2,2,0,3,3,4,5,6,7 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake","Selection"
	./Execute --Input Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/SystematicsZG.$(Format) \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake"
	./Execute --Input Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/SystematicsRG.$(Format) \
		--GenPrimaryMin 0 --GenPrimaryMax 0.4999 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake"
	./Execute --Input Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/SystematicsMG.$(Format) \
		--GenPrimaryMin -0.1 --GenPrimaryMax 15 \
		--WorldXMin -0.1 --WorldXMax 15 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet M_{G}" --YLabel "Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake"
	./Execute --Input Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/SystematicsMGE.$(Format) \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 0.5 --LogY false \
		--XLabel "Jet M_{G} / E" --YLabel "Uncertainty" --Binning "Jet E" \
		--LegendX 0.15 --LegendY 0.2 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--Variations HJECUp,HJECDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake \
		--SystematicGroups 1,1,2,2,3,3,3,4,5,6 \
		--Labels "JEC","JER","Unfold","SVD","Closure","Fake"
	# cp -f Plots/Meow*.pdf ~/WindowsHome/Downloads/

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
