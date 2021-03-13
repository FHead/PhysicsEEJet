
default: TestRun

TestRun: Execute
	./Execute --Input Input/ToyJetPNominal.root  --Output IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyJetZGNominal.root --Output IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyJetRGNominal.root --Output IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetPNominal.root  --Output DataIterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetZGNominal.root --Output DataIterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataJetRGNominal.root --Output DataIterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound2JetPNominal.root  --Output DataRound2IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound2JetZGNominal.root --Output DataRound2IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound2JetRGNominal.root --Output DataRound2IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound3JetPNominal.root  --Output DataRound3IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound3JetZGNominal.root --Output DataRound3IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound3JetRGNominal.root --Output DataRound3IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound4JetPNominal.root  --Output DataRound4IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound4JetZGNominal.root --Output DataRound4IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound4JetRGNominal.root --Output DataRound4IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound5JetPNominal.root  --Output DataRound5IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound5JetZGNominal.root --Output DataRound5IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound5JetRGNominal.root --Output DataRound5IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound6JetPNominal.root  --Output DataRound6IterationScanJetP.pdf  --Ignore 10 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound6JetZGNominal.root --Output DataRound6IterationScanJetZG.pdf --Ignore 18 --Reference HMCTruth
	./Execute --Input Input/ToyDataRound6JetRGNominal.root --Output DataRound6IterationScanJetRG.pdf --Ignore 24 --Reference HMCTruth

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute


