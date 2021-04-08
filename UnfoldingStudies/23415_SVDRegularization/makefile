
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23412_ActualUnfold/Unfolded Input

TestRun: Execute
	# ./Execute --Input Input/ToyJetENominal.root  --Output RegularizationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyLeadingDiJetENominal.root  --Output RegularizationScanLeadingDiJetE.pdf  --Ignore 10 --Reference HMCTruth
	# ./Execute --Input Input/ToyJetZGNominal.root --Output RegularizationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	# ./Execute --Input Input/ToyJetRGNominal.root --Output RegularizationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMGNominal.root --Output RegularizationScanJetMG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMGENominal.root --Output RegularizationScanJetMGE.pdf --Ignore 24 --Reference HMCTruth

TestRunData: Execute
	# ./Execute --Input Input/ToyDataJetENominal.root  --Output DataRegularizationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataLeadingDiJetENominal.root  --Output DataRegularizationScanLeadingDiJetE.pdf  --Ignore 10 --Reference HMCTruth
	# ./Execute --Input Input/ToyDataJetZGNominal.root --Output DataRegularizationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	# ./Execute --Input Input/ToyDataJetRGNominal.root --Output DataRegularizationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMGNominal.root --Output DataRegularizationScanJetMG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMGENominal.root --Output DataRegularizationScanJetMGE.pdf --Ignore 24 --Reference HMCTruth

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute


