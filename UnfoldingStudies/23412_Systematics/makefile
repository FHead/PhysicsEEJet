default: RunData RunDataPlot

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23411_UnfoldingPreparation/Output BinMapping

RunData: Execute
	./Execute \
		--BaseInput Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root \
		--Input Input/DataJetEJECUp.root,Input/DataJetEJECDown.root,Input/DataJetEJECHalfUp.root,Input/DataJetEJECHalfDown.root,Input/DataJetEJERUp.root,Input/DataJetEJERDown.root,Input/DataJetEMCPrior.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes15,HUnfoldedBayes19,HUnfoldedSVD,HUnfoldedBayes14 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure \
		--Group 1,1,0,0,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetENominal.root \
		--DoSelfNormalize false \
		--Output DataJetE.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD,HUnfoldedBayes14 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure \
		--Group 1,1,0,0,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetZG.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD,HUnfoldedBayes14 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure \
		--Group 1,1,0,0,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetZGNormalized.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD,HUnfoldedBayes14 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure \
		--Group 1,1,0,0,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetRG.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD,HUnfoldedBayes14 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure \
		--Group 1,1,0,0,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetRGNormalized.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetE.root --Output PlotDataJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure"
	./ExecutePlot --Input DataJetZG.root --Output PlotDataJetZG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure"
	./ExecutePlot --Input DataJetZGNormalized.root --Output PlotDataJetZGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure"
	./ExecutePlot --Input DataJetRG.root --Output PlotDataJetRG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure"
	./ExecutePlot --Input DataJetRGNormalized.root --Output PlotDataJetRGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





