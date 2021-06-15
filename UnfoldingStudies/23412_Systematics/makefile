default: RunData RunDataPlot

Prepare:
	rm -f Input BinMapping
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23411_UnfoldingPreparation/Output BinMapping
	ln -sf ../23411_UnfoldingPreparation/Output OriginalInput
	ln -sf ../23545_LeadingDiJetUncertainty Leading
	ln -sf ../23551_JetReweightingUncertainty Correction

RunData: RunDataJetE RunDataDiJetE RunDataDiJetSumE RunDataJetZG RunDataJetRG \
	RunDataJetMG RunDataJetMGE RunDataJetM RunDataJetME RunDataPlot

RunDataJetE: Execute
	./Execute \
		--BaseInput Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetEPositiveTheta.root \
		--Input Input/DataJetEJECUp.root,Input/DataJetEJECDown.root,Input/DataJetEJECHalfUp.root,Input/DataJetEJECHalfDown.root,Input/DataJetEJERUp.root,Input/DataJetEJERDown.root,Input/DataJetEMCPrior.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/DataJetENominal.root,Input/MCJetENominal.root,Input/DataJetELargeThetaGap.root,Input/MCJetEFake.root,Input/DataJetENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes15,HUnfoldedBayes19,HUnfoldedSVD12.0,HUnfoldedBayes14,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 3,3,3,3,3,3,3,0,0,0,0,2,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetENominal.root \
		--DoSelfNormalize false \
		--Output DataJetE.root

RunDataDiJetE: Execute
	./Execute \
		--BaseInput Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetEPositiveTheta.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Leading/DijetJetE.root,Correction/LeadingDiJetE.root \
		--Input Input/DataLeadingDiJetEJECUp.root,Input/DataLeadingDiJetEJECDown.root,Input/DataLeadingDiJetEJECHalfUp.root,Input/DataLeadingDiJetEJECHalfDown.root,Input/DataLeadingDiJetEJERUp.root,Input/DataLeadingDiJetEJERDown.root,Input/DataLeadingDiJetEMCPrior.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/DataLeadingDiJetENominal.root,Input/MCLeadingDiJetENominal.root,Input/DataLeadingDiJetELargeThetaGap.root,Input/MCLeadingDiJetEFake.root,Input/DataLeadingDiJetENegativeTheta.root,Input/DataLeadingDiJetELowerSumE.root,Input/DataLeadingDiJetEHigherSumE.root,Input/MCLeadingDiJetESmearedSumE.root,Leading/DijetJetE.root,Correction/LeadingDiJetE.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HNominal,HOriginal \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD4.0,HUnfoldedBayes1,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HSymmetrized,HVariation \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side,LowSumE,HighSumE,SmearSumE,CorrectionFit,CorrectionMC \
		--Group 1,1,0,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1 \
		--Bridging 3,3,3,3,3,3,3,0,0,0,0,2,0,0,0,0,2,0,2 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataLeadingDiJetENominal.root \
		--DoSelfNormalize true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false \
		--Output DataLeadingDiJetE.root

RunDataDiJetSumE: Execute
	./Execute \
		--BaseInput Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/MCLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/MCLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumEPositiveTheta.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/MCLeadingDiJetSumENominal.root,Leading/DijetSumE.root,Correction/LeadingDiJetSumE.root \
		--Input Input/DataLeadingDiJetSumEJECUp.root,Input/DataLeadingDiJetSumEJECDown.root,Input/DataLeadingDiJetSumEJECHalfUp.root,Input/DataLeadingDiJetSumEJECHalfDown.root,Input/DataLeadingDiJetSumEJERUp.root,Input/DataLeadingDiJetSumEJERDown.root,Input/DataLeadingDiJetSumEMCPrior.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumENominal.root,Input/MCLeadingDiJetSumENominal.root,Input/DataLeadingDiJetSumELargeThetaGap.root,Input/MCLeadingDiJetSumEFake.root,Input/DataLeadingDiJetSumENegativeTheta.root,Input/DataLeadingDiJetSumELowerSumE.root,Input/DataLeadingDiJetSumEHigherSumE.root,Input/MCLeadingDiJetSumESmearedSumE.root,Leading/DijetSumE.root,Correction/LeadingDiJetSumE.root \
		--BaseHistogram HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HMCTruth,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HNominal,HOriginal \
		--Histogram HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes14,HUnfoldedBayes16,HUnfoldedSVD6.0,HUnfoldedBayes1,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HUnfoldedBayes15,HSymmetrized,HVariation \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side,LowSumE,HighSumE,SmearSumE,CorrectionFit,CorrectionMC \
		--Group 1,1,0,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1 \
		--Bridging 3,3,3,3,3,3,3,0,0,2,0,2,0,0,0,0,0,0,2 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataLeadingDiJetSumENominal.root \
		--DoSelfNormalize true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false \
		--Output DataLeadingDiJetSumE.root

RunDataJetZG: Execute
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGPositiveTheta.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root,Input/MCJetZGFake.root,Input/DataJetZGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes16,HUnfoldedBayes18,HUnfoldedSVD29.0,HUnfoldedBayes14,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetZG.root
	./Execute \
		--BaseInput Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGPositiveTheta.root \
		--Input Input/DataJetZGJECUp.root,Input/DataJetZGJECDown.root,Input/DataJetZGJECHalfUp.root,Input/DataJetZGJECHalfDown.root,Input/DataJetZGJERUp.root,Input/DataJetZGJERDown.root,Input/DataJetZGMCPrior.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/DataJetZGNominal.root,Input/MCJetZGNominal.root,Input/DataJetZGLargeThetaGap.root,Input/MCJetZGFake.root,Input/DataJetZGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HMCTruth,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Histogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes16,HUnfoldedBayes18,HUnfoldedSVD29.0,HUnfoldedBayes14,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1.16120166997,1,1 \
		--BinMapping BinMapping/DataJetZGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetZGNormalized.root

RunDataJetRG: Execute
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGPositiveTheta.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root,Input/MCJetRGFake.root,Input/DataJetRGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HMCTruth,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8 \
		--Histogram HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes7,HUnfoldedBayes9,HUnfoldedSVD42.0,HUnfoldedBayes14,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetRG.root
	./Execute \
		--BaseInput Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGPositiveTheta.root \
		--Input Input/DataJetRGJECUp.root,Input/DataJetRGJECDown.root,Input/DataJetRGJECHalfUp.root,Input/DataJetRGJECHalfDown.root,Input/DataJetRGJERUp.root,Input/DataJetRGJERDown.root,Input/DataJetRGMCPrior.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/DataJetRGNominal.root,Input/MCJetRGNominal.root,Input/DataJetRGLargeThetaGap.root,Input/MCJetRGFake.root,Input/DataJetRGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HMCTruth,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8 \
		--Histogram HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes7,HUnfoldedBayes9,HUnfoldedSVD42.0,HUnfoldedBayes14,HUnfoldedBayes8,HUnfoldedBayes8,HUnfoldedBayes8 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetRGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetRGNormalized.root

RunDataJetMG: Execute
	./Execute \
		--BaseInput Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGPositiveTheta.root \
		--Input Input/DataJetMGJECUp.root,Input/DataJetMGJECDown.root,Input/DataJetMGJECHalfUp.root,Input/DataJetMGJECHalfDown.root,Input/DataJetMGJERUp.root,Input/DataJetMGJERDown.root,Input/DataJetMGMCPrior.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGLargeThetaGap.root,Input/MCJetMGFake.root,Input/DataJetMGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HMCTruth,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Histogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes15,HUnfoldedBayes17,HUnfoldedSVD32.0,HUnfoldedBayes14,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGNominal.root \
		--DoSelfNormalize false \
		--Output DataJetMG.root
	./Execute \
		--BaseInput Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGPositiveTheta.root \
		--Input Input/DataJetMGJECUp.root,Input/DataJetMGJECDown.root,Input/DataJetMGJECHalfUp.root,Input/DataJetMGJECHalfDown.root,Input/DataJetMGJERUp.root,Input/DataJetMGJERDown.root,Input/DataJetMGMCPrior.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/DataJetMGNominal.root,Input/MCJetMGNominal.root,Input/DataJetMGLargeThetaGap.root,Input/MCJetMGFake.root,Input/DataJetMGNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HMCTruth,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Histogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes15,HUnfoldedBayes17,HUnfoldedSVD32.0,HUnfoldedBayes14,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGNominal.root \
		--DoSelfNormalize true \
		--Output DataJetMGNormalized.root

RunDataJetMGE: Execute
	./Execute \
		--BaseInput Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGEPositiveTheta.root \
		--Input Input/DataJetMGEJECUp.root,Input/DataJetMGEJECDown.root,Input/DataJetMGEJECHalfUp.root,Input/DataJetMGEJECHalfDown.root,Input/DataJetMGEJERUp.root,Input/DataJetMGEJERDown.root,Input/DataJetMGEMCPrior.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGELargeThetaGap.root,Input/MCJetMGEFake.root,Input/DataJetMGENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HMCTruth,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Histogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes15,HUnfoldedBayes17,HUnfoldedSVD34.0,HUnfoldedBayes14,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGENominal.root \
		--DoSelfNormalize false \
		--Output DataJetMGE.root
	./Execute \
		--BaseInput Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGEPositiveTheta.root \
		--Input Input/DataJetMGEJECUp.root,Input/DataJetMGEJECDown.root,Input/DataJetMGEJECHalfUp.root,Input/DataJetMGEJECHalfDown.root,Input/DataJetMGEJERUp.root,Input/DataJetMGEJERDown.root,Input/DataJetMGEMCPrior.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/DataJetMGENominal.root,Input/MCJetMGENominal.root,Input/DataJetMGELargeThetaGap.root,Input/MCJetMGEFake.root,Input/DataJetMGENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HMCTruth,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Histogram HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes15,HUnfoldedBayes17,HUnfoldedSVD34.0,HUnfoldedBayes14,HUnfoldedBayes16,HUnfoldedBayes16,HUnfoldedBayes16 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMGENominal.root \
		--DoSelfNormalize true \
		--Output DataJetMGENormalized.root

RunDataJetM: Execute
	./Execute \
		--BaseInput Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMPositiveTheta.root \
		--Input Input/DataJetMJECUp.root,Input/DataJetMJECDown.root,Input/DataJetMJECHalfUp.root,Input/DataJetMJECHalfDown.root,Input/DataJetMJERUp.root,Input/DataJetMJERDown.root,Input/DataJetMMCPrior.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMLargeThetaGap.root,Input/MCJetMFake.root,Input/DataJetMNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes7,HUnfoldedSVD21.0,HUnfoldedBayes14,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMNominal.root \
		--DoSelfNormalize false \
		--Output DataJetM.root
	./Execute \
		--BaseInput Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMPositiveTheta.root \
		--Input Input/DataJetMJECUp.root,Input/DataJetMJECDown.root,Input/DataJetMJECHalfUp.root,Input/DataJetMJECHalfDown.root,Input/DataJetMJERUp.root,Input/DataJetMJERDown.root,Input/DataJetMMCPrior.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/DataJetMNominal.root,Input/MCJetMNominal.root,Input/DataJetMLargeThetaGap.root,Input/MCJetMFake.root,Input/DataJetMNegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD11.0,HUnfoldedBayes14,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMNominal.root \
		--DoSelfNormalize true \
		--Output DataJetMNormalized.root

RunDataJetME: Execute
	./Execute \
		--BaseInput Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMEPositiveTheta.root \
		--Input Input/DataJetMEJECUp.root,Input/DataJetMEJECDown.root,Input/DataJetMEJECHalfUp.root,Input/DataJetMEJECHalfDown.root,Input/DataJetMEJERUp.root,Input/DataJetMEJERDown.root,Input/DataJetMEMCPrior.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMELargeThetaGap.root,Input/MCJetMEFake.root,Input/DataJetMENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD29.0,HUnfoldedBayes14,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMENominal.root \
		--DoSelfNormalize false \
		--Output DataJetME.root
	./Execute \
		--BaseInput Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMEPositiveTheta.root \
		--Input Input/DataJetMEJECUp.root,Input/DataJetMEJECDown.root,Input/DataJetMEJECHalfUp.root,Input/DataJetMEJECHalfDown.root,Input/DataJetMEJERUp.root,Input/DataJetMEJERDown.root,Input/DataJetMEMCPrior.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/DataJetMENominal.root,Input/MCJetMENominal.root,Input/DataJetMELargeThetaGap.root,Input/MCJetMEFake.root,Input/DataJetMENegativeTheta.root \
		--BaseHistogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HMCTruth,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Histogram HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes6,HUnfoldedBayes8,HUnfoldedSVD29.0,HUnfoldedBayes14,HUnfoldedBayes7,HUnfoldedBayes7,HUnfoldedBayes7 \
		--Label JECUp,JECDown,JECHalfUp,JECHalfDown,JERUp,JERDown,MCPrior,IterationDown,IterationUp,SVD,MCClosure,ThetaGap,Fake,Side \
		--Group 1,1,0,0,1,1,1,1,1,1,1,0,1,0 \
		--Bridging 0,0,0,0,0,0,0,0,0,0,0,0,0,0 \
		--ExtraScaling 1,1,1,1,1,1,1,1,1,1,1,1,1,1 \
		--BinMapping BinMapping/DataJetMENominal.root \
		--DoSelfNormalize true \
		--Output DataJetMENormalized.root

RunDataPlot: ExecutePlot
	./ExecutePlot --Input DataJetE.root --Output PlotDataJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataLeadingDiJetE.root --Output PlotDataLeadingDiJetE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HLowSumE,HHighSumE,HSmearSumE,"HCorrectionFit","HCorrectionMC" \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","Fake","Sum E-","Sum E+","Smear Sum E","Correction Fit","Correction MC"
	./ExecutePlot --Input DataLeadingDiJetSumE.root --Output PlotDataLeadingDiJetSumE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HFake,HLowSumE,HHighSumE,HSmearSumE,HCorrectionFit,HCorrectionMC \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","Fake","Sum E-","Sum E+","Smear Sum E","Correction Fit","Correction MC"
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
	./ExecutePlot --Input DataJetMGE.root --Output PlotDataJetMGE.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetMGENormalized.root --Output PlotDataJetMGENormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetM.root --Output PlotDataJetM.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetMNormalized.root --Output PlotDataJetMNormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetME.root --Output PlotDataJetME.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"
	./ExecutePlot --Input DataJetMENormalized.root --Output PlotDataJetMENormalized.pdf \
		--Variations HJECUp,HJECDown,HJECHalfUp,HJECHalfDown,HJERUp,HJERDown,HMCPrior,HIterationDown,HIterationUp,HSVD,HMCClosure,HThetaGap,HFake,HSide \
		--Labels "JEC Up","JEC Down","JEC Up 0.5x","JEC Down 0.5x","JER Up","JER Down","MC Prior","Iteration Down","Iteration Up","SVD","Closure","ThetaGap","Fake","Side"

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot





