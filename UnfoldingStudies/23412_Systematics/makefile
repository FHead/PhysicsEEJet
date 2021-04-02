default: RunData RunDataPlot

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23411_UnfoldingPreparation/Output BinMapping

RunData: Execute
	./Execute \
		--BaseInput Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetENominal.root \
		--Input Input/DataJetEJECUp.root,Input/DataJetEJECDown.root,Input/DataJetEJECHalfUp.root,Input/DataJetEJECHalfDown.root,Input/DataJetEJERUp.root,Input/DataJetEJERDown.root,Input/DataJetEMCPrior.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetELargeThetaGap.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes15,HUnfoldedBayes19,HUnfoldedSVD12.0,HUnfoldedBayes14,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap \
		--Group 1,1,0,0,1,1,1,1,1,1,1,1 \
		--Bridging 2,2,2,2,2,2,2,0,0,0,0,2 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997 \
		--BinMapping BinMapping/DataJetENominal.root \
		--DoSelfNormalize false \
		--Output DataJetE.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD27.0,HUnfoldedBayes14,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetZG.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD27.0,HUnfoldedBayes14,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetZGNormalized.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetRG.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetRGNormalized.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetE.root --Output PlotDataJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap"
	./ExecutePlot --Input DataJetZG.root --Output PlotDataJetZG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap"
	./ExecutePlot --Input DataJetZGNormalized.root --Output PlotDataJetZGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap"
	./ExecutePlot --Input DataJetRG.root --Output PlotDataJetRG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap"
	./ExecutePlot --Input DataJetRGNormalized.root --Output PlotDataJetRGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





