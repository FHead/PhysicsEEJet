
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23412_ActualUnfold/Unfolded Input

TestRun: Execute
	./Execute --Input Input/ToyJetENominal.root  --Output IterationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyJetZGNominal.root --Output IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyJetRGNominal.root --Output IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth

TestRunData: Execute
	./Execute --Input Input/ToyDataJetENominal.root  --Output DataIterationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetZGNominal.root --Output DataIterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetRGNominal.root --Output DataIterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute


