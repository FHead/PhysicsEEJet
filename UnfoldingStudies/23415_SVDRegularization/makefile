
default: TestRun TestRunData

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded Input

TestRun: Execute
	./Execute --Input Input/ToyJetENominal.root  --Output RegularizationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyJetZGNominal.root --Output RegularizationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyJetRGNominal.root --Output RegularizationScanJetRG.pdf --Ignore 24 --Reference HMCTruth

TestRunData: Execute
	./Execute --Input Input/ToyDataJetENominal.root  --Output DataRegularizationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetZGNominal.root --Output DataRegularizationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetRGNominal.root --Output DataRegularizationScanJetRG.pdf --Ignore 24 --Reference HMCTruth

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute

