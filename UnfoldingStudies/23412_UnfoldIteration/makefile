
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23412_ActualUnfold/Unfolded Input

TestRun: Execute
	./Execute --Input Input/ToyJetENominal.root  --Output IterationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyLeadingDiJetENominal.root  --Output IterationScanLeadingDiJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyLeadingDiJetSumENominal.root  --Output IterationScanLeadingDiJetSumE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyJetZGNominal.root --Output IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyJetRGNominal.root --Output IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMGNominal.root --Output IterationScanJetMG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMGENominal.root --Output IterationScanJetMGE.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMNominal.root --Output IterationScanJetM.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyJetMENominal.root --Output IterationScanJetME.pdf --Ignore 24 --Reference HMCTruth

TestRunData: Execute
	./Execute --Input Input/ToyDataJetENominal.root  --Output DataIterationScanJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataLeadingDiJetENominal.root  --Output DataIterationScanLeadingDiJetE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataLeadingDiJetSumENominal.root  --Output DataIterationScanLeadingDiJetSumE.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetZGNominal.root --Output DataIterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetRGNominal.root --Output DataIterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMGNominal.root --Output DataIterationScanJetMG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMGENominal.root --Output DataIterationScanJetMGE.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMNominal.root --Output DataIterationScanJetM.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetMENominal.root --Output DataIterationScanJetME.pdf --Ignore 24 --Reference HMCTruth

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute


