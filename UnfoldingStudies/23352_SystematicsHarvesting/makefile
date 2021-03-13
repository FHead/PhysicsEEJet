default: RunData RunDataPlot

RunData: Execute
	./Execute \
		--Input Input/DataJetPNominal.root,Input/DataJetPJECUp.root,Input/DataJetPJECDown.root,Input/DataJetPJECHalfUp.root,Input/DataJetPJECHalfDown.root,Input/DataJetPJERUp.root,Input/DataJetPJERDown.root,Input/DataJetPMCPrior.root,Input/DataJetPNominal.root,Input/DataJetPNominal.root,Input/DataJetPNominal.root \
		--Histogram HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes14,HUnfoldedBayes12,HUnfoldedBayes16,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--BinMapping BinMapping/DataJetPNominal.root \
		--Output DataJetP.root
	./Execute \
		--Input Input/DataJetZGNominal.root,Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root \
		--Histogram HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes11,HUnfoldedBayes9,HUnfoldedBayes14,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--Output DataJetZG.root
	./Execute \
		--Input Input/DataJetRGNominal.root,Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes5,HUnfoldedBayes9,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--Output DataJetRG.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetP.root --Output PlotDataJetP.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetZG.root --Output PlotDataJetZG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetRG.root --Output PlotDataJetRG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





