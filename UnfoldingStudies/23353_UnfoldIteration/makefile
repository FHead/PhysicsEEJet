
default: TestRun

TestRun: Execute
	./Execute --Input Input/MCJetPNominal.root  --Output IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/MCJetZGNominal.root --Output IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/MCJetRGNominal.root --Output IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/MCJetPNominal.root  --Output IterationScanJetP_U.pdf  --Ignore 10 --Reference HUnfoldedBayes500
	./Execute --Input Input/MCJetZGNominal.root --Output IterationScanJetZG_U.pdf --Ignore 18 --Reference HUnfoldedBayes500
	./Execute --Input Input/MCJetRGNominal.root --Output IterationScanJetRG_U.pdf --Ignore 24 --Reference HUnfoldedBayes500

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute


