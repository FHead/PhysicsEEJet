default: RunData RunDataPlot

RunData: Execute
	./Execute \
		--Input Input/DataJetENominal.root,Input/DataJetEJECUp.root,Input/DataJetEJECDown.root,Input/DataJetEJECHalfUp.root,Input/DataJetEJECHalfDown.root,Input/DataJetEJERUp.root,Input/DataJetEJERDown.root,Input/DataJetEMCPrior.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root \
		--Histogram HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes19,HUnfoldedBayes17,HUnfoldedBayes21,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--Group 0,1,1,0,0,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetENominal.root \
		--DoSelfNormalize false \
		--Output DataJetE.root
	./Execute \
		--Input Input/DataJetZGNominal.root,Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--Group 0,1,1,0,0,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetZG.root
	./Execute \
		--Input Input/DataJetZGNominal.root,Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--Group 0,1,1,0,0,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetZGNormalized.root
	./Execute \
		--Input Input/DataJetRGNominal.root,Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--Group 0,1,1,0,0,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetRG.root
	./Execute \
		--Input Input/DataJetRGNominal.root,Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD \
		--Label Nominal,JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD \
		--Group 0,1,1,0,0,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetRGNormalized.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetE.root --Output PlotDataJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetZG.root --Output PlotDataJetZG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetZGNormalized.root --Output PlotDataJetZGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetRG.root --Output PlotDataJetRG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"
	./ExecutePlot --Input DataJetRGNormalized.root --Output PlotDataJetRGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





