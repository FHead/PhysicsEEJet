default: RunData RunDataPlot

Prepare:
	rm -f Input BinMapping
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23411_UnfoldingPreparation/Output BinMapping

RunData: Execute
	./Execute \
		--BaseInput Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetENominal.root,BinMapping/MCJetENominal.root,Input/DataJetEPositiveTheta.root \
		--Input Input/DataJetEJECUp.root,Input/DataJetEJECDown.root,Input/DataJetEJECHalfUp.root,Input/DataJetEJECHalfDown.root,Input/DataJetEJERUp.root,Input/DataJetEJERDown.root,Input/DataJetEMCPrior.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetELargeThetaGap.root,BinMapping/MCJetENominal.root,Input/DataJetENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17,HMCMatchedGenBin,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes15,HUnfoldedBayes19,HUnfoldedSVD12.0,HUnfoldedBayes14,HUnfoldedBayes17,HMCRecoGenBin,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 2,2,2,2,2,2,2,0,0,0,0,2,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetENominal.root \
		--DoSelfNormalize false \
		--Output DataJetE.root
	./Execute \
		--BaseInput Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,BinMapping/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetEPositiveTheta.root \
		--Input Input/DataLeadingDiJetEJECUp.root,Input/DataLeadingDiJetEJECDown.root,Input/DataLeadingDiJetEJECHalfUp.root,Input/DataLeadingDiJetEJECHalfDown.root,Input/DataLeadingDiJetEJERUp.root,Input/DataLeadingDiJetEJERDown.root,Input/DataLeadingDiJetEMCPrior.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetELargeThetaGap.root,BinMapping/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17,HMCMatchedGenBin,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes15,HUnfoldedBayes19,HUnfoldedSVD12.0,HUnfoldedBayes14,HUnfoldedBayes17,HMCRecoGenBin,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 2,2,2,2,2,2,2,0,0,0,0,2,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataLeadingDiJetENominal.root \
		--DoSelfNormalize false \
		--Output DataLeadingDiJetE.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root,BinMapping/MCJetZGNominal.root,Input/DataJetZGPositiveTheta.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root,BinMapping/MCJetZGNominal.root,Input/DataJetZGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HMCMatchedGenBin,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD27.0,HUnfoldedBayes14,HUnfoldedBayes7,HMCRecoGenBin,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetZG.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root,BinMapping/MCJetZGNominal.root,Input/DataJetZGPositiveTheta.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root,BinMapping/MCJetZGNominal.root,Input/DataJetZGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HMCMatchedGenBin,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD27.0,HUnfoldedBayes14,HUnfoldedBayes7,HMCRecoGenBin,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetZGNormalized.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root,BinMapping/MCJetRGNominal.root,Input/DataJetRGPositiveTheta.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root,BinMapping/MCJetRGNominal.root,Input/DataJetRGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9,HMCMatchedGenBin,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9,HMCRecoGenBin,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetRG.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root,BinMapping/MCJetRGNominal.root,Input/DataJetRGPositiveTheta.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root,BinMapping/MCJetRGNominal.root,Input/DataJetRGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9,HMCMatchedGenBin,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9,HMCRecoGenBin,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetRGNormalized.root
	./Execute \
		--BaseInput Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGNominal.root,BinMapping/MCJetMGNominal.root,Input/DataJetMGPositiveTheta.root \
		--Input Input/DataJetMGJECUp.root,Input/DataJetMGJECDown.root,Input/DataJetMGJECHalfUp.root,Input/DataJetMGJECHalfDown.root,Input/DataJetMGJERUp.root,Input/DataJetMGJERDown.root,Input/DataJetMGMCPrior.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGLargeThetaGap.root,BinMapping/MCJetMGNominal.root,Input/DataJetMGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9,HMCMatchedGenBin,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9,HMCRecoGenBin,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetMG.root
	./Execute \
		--BaseInput Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGNominal.root,BinMapping/MCJetMGNominal.root,Input/DataJetMGPositiveTheta.root \
		--Input Input/DataJetMGJECUp.root,Input/DataJetMGJECDown.root,Input/DataJetMGJECHalfUp.root,Input/DataJetMGJECHalfDown.root,Input/DataJetMGJERUp.root,Input/DataJetMGJERDown.root,Input/DataJetMGMCPrior.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGLargeThetaGap.root,BinMapping/MCJetMGNominal.root,Input/DataJetMGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HMCTruth,HUnfoldedBayes9,HMCMatchedGenBin,HUnfoldedBayes9 \
		--Histogram HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes9,HUnfoldedBayes8,HUnfoldedBayes10,HUnfoldedSVD40.0,HUnfoldedBayes14,HUnfoldedBayes9,HMCRecoGenBin,HUnfoldedBayes9 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetMGNormalized.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetE.root --Output PlotDataJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataLeadingDiJetE.root --Output PlotDataLeadingDiJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetZG.root --Output PlotDataJetZG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetZGNormalized.root --Output PlotDataJetZGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetRG.root --Output PlotDataJetRG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetRGNormalized.root --Output PlotDataJetRGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetMG.root --Output PlotDataJetMG.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetMGNormalized.root --Output PlotDataJetMGNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





