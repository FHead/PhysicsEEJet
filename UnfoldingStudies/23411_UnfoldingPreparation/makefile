
GenJetEBins = 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45
RecoJetEBins = 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,52.5,55,57.5,60,65,70,80,90
# RecoJetEBins = 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,50,55,60,65,70,80,90
# GenJetE1Bins = 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44
# RecoJetE1Bins = 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,50,60,70,90
# GenJetE2Bins = 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44
# RecoJetE2Bins = 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,50,60,70,90
GenJetE1Bins = 3,6,9,12,15,18,21,24,27,30,33,36,39,42,44
RecoJetE1Bins = 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,50,60,70,90
GenJetE2Bins = 3,6,9,12,15,18,21,24,27,30,33,36,39,42,44
RecoJetE2Bins = 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,50,60,70,90
GenJetECoarseBins = 5,10,15,20,25,30,35,40
RecoJetECoarseBins = 5,10,15,20,25,30,35,40,45,50,60
GenJetZGBins = 0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45
RecoJetZGBins = 0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45
GenJetRGBins = 0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45
RecoJetRGBins = 0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45
GenJetMGBins = 0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0
RecoJetMGBins = 0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0
GenJetMGEBins = 0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26
RecoJetMGEBins = 0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26
GenThrustBins = 0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985
RecoThrustBins = 0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985
GenThrustUniformBins = 0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99
RecoThrustUniformBins = 0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99

MGEMin = 0.0

default: ThrustNominalRun ThrustNoCutRun

RunAll: Preparation DataNominalRun MCNominalRun MCNoJECRun DataJECRunHalf DataNoResidualRun DataJECRun DataJERRun \
	DataLargeThetaGapRun MCLargeThetaGapRun DataThetaSideRun MCThetaSideRun \
	ThrustNominalRun ThrustNoCutRun MCExtra

Preparation:
	ln -sf ../23411_JetResponseClustering/*root .
	mkdir -p Output/

ThrustNominalRun: Execute
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataThrustNominal.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustBins) \
		--ObservableRecoBins $(RecoThrustBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCThrustNominal.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustBins) \
		--ObservableRecoBins $(RecoThrustBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataThrustUniform.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustUniformBins) \
		--ObservableRecoBins $(RecoThrustUniformBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCThrustUniform.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustUniformBins) \
		--ObservableRecoBins $(RecoThrustUniformBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1

ThrustNoCutRun: Execute
	time ./Execute --MC MCNoCut.root --Data DataNoCut.root --Output Output/DataNoCutThrustNominal.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustBins) \
		--ObservableRecoBins $(RecoThrustBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCNoCut.root --Data MCNoCut.root --Output Output/MCNoCutThrustNominal.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustBins) \
		--ObservableRecoBins $(RecoThrustBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCNoCut.root --Data DataNoCut.root --Output Output/DataNoCutThrustUniform.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustUniformBins) \
		--ObservableRecoBins $(RecoThrustUniformBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCNoCut.root --Data MCNoCut.root --Output Output/MCNoCutThrustUniform.root --CheckMatchAngle false \
		--Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenThrustUniformBins) \
		--ObservableRecoBins $(RecoThrustUniformBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1

DataThetaSideRun: Execute
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataJetEPositiveTheta.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataLeadingDiJetEPositiveTheta.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataJetZGPositiveTheta.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataJetRGPositiveTheta.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataJetMGPositiveTheta.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data DataPositiveTheta.root --Output Output/DataJetMGEPositiveTheta.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataJetENegativeTheta.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataLeadingDiJetENegativeTheta.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataJetZGNegativeTheta.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataJetRGNegativeTheta.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataJetMGNegativeTheta.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data DataNegativeTheta.root --Output Output/DataJetMGENegativeTheta.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

DataLargeThetaGapRun: Execute
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataJetELargeThetaGap.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataLeadingDiJetELargeThetaGap.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataJetZGLargeThetaGap.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataJetRGLargeThetaGap.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataJetMGLargeThetaGap.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root --Output Output/DataJetMGELargeThetaGap.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

MCThetaSideRun: Execute
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCJetEPositiveTheta.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCLeadingDiJetEPositiveTheta.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCJetZGPositiveTheta.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCJetRGPositiveTheta.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCJetMGPositiveTheta.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCPositiveTheta.root --Data MCPositiveTheta.root --Output Output/MCJetMGEPositiveTheta.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCJetENegativeTheta.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCLeadingDiJetENegativeTheta.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCJetZGNegativeTheta.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCJetRGNegativeTheta.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCJetMGNegativeTheta.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCNegativeTheta.root --Data MCNegativeTheta.root --Output Output/MCJetMGENegativeTheta.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

MCLargeThetaGapRun: Execute
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCJetELargeThetaGap.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCLeadingDiJetELargeThetaGap.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCJetZGLargeThetaGap.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCJetRGLargeThetaGap.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCJetMGLargeThetaGap.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root --Output Output/MCJetMGELargeThetaGap.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

DataNominalRun: Execute
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetENominal.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingJetENominal.root \
		--Observable LeadingJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetENominal.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGNominal.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGNominal.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGNominal.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGENominal.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZG2Nominal.root \
		--Observable JetZG --ObservableIndex 1 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRG2Nominal.root \
		--Observable JetRG --ObservableIndex 1 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMG2Nominal.root \
		--Observable JetMG --ObservableIndex 1 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGE2Nominal.root \
		--Observable JetMGE --ObservableIndex 1 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

DataJECRun: Execute
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJECUp.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJECDown.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJECUp.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJECDown.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJECUp.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJECDown.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJECUp.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJECDown.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJECUp.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJECDown.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJECUp.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 1 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJECDown.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -1 \
		--BinningUncertaintySmear 1.025

DataJECRunHalf: Execute
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJECHalfUp.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.5 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJECHalfDown.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -0.5 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJECHalfUp.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.5 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJECHalfDown.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -0.5 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJECHalfUp.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJECHalfDown.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJECHalfUp.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJECHalfDown.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJECHalfUp.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJECHalfDown.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJECHalfUp.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift 0.5 \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJECHalfDown.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintyShift -0.5 \
		--BinningUncertaintySmear 1.025

DataJERRun: Execute
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJERUp.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJERUp.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJERUp.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJERUp.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJERUp.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJERUp.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.05
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetEJERDown.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.00
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataLeadingDiJetEJERDown.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.00
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetZGJERDown.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.00
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetRGJERDown.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.00
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGJERDown.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.00
	time ./Execute --MC MC.root --Data Data.root --Output Output/DataJetMGEJERDown.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.00

DataNoResidualRun: Execute
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataJetENoResidual.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataLeadingDiJetENoResidual.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1 \
		--ObservableUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataJetZGNoResidual.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataJetRGNoResidual.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataJetMGNoResidual.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025
	time ./Execute --MC MC.root --Data DataNoResidual.root --Output Output/DataJetMGENoResidual.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins) \
		--BinningUncertaintySmear 1.025

MCNominalRun: Execute
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetENominal.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCLeadingJetENominal.root \
		--Observable LeadingJetE --ObservableIndex -1 --Binning SubleadingJetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetE1Bins) \
		--ObservableRecoBins $(RecoJetE1Bins) \
		--BinningGenBins $(GenJetE2Bins) \
		--BinningRecoBins $(RecoJetE2Bins)
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCLeadingDiJetENominal.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetZGNominal.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetRGNominal.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetMGNominal.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetMGENominal.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetMGELowECut.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin 2 --BinningRecoMin 2 \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)

MCNoJECRun: Execute
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCJetENoJEC.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCLeadingDiJetENoJEC.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCJetZGNoJEC.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCJetRGNoJEC.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCJetMGNoJEC.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCNoJEC.root --Data MCNoJEC.root --Output Output/MCJetMGENoJEC.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)

MCExtra: Execute
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8JetE.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8LeadingDiJetE.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8JetZG.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8JetRG.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8JetMG.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCPythia8.root --Data MCPythia8.root --Output Output/MCPythia8JetMGE.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigJetE.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigLeadingDiJetE.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigJetZG.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigJetRG.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigJetMG.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCHerwig.root --Data MCHerwig.root --Output Output/MCHerwigJetMGE.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaJetE.root \
		--Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaLeadingDiJetE.root \
		--Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenJetEBins) \
		--ObservableRecoBins $(RecoJetEBins) \
		--BinningGenBins 0,1 \
		--BinningRecoBins 0,1
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaJetZG.root \
		--Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetZGBins) \
		--ObservableRecoBins $(RecoJetZGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaJetRG.root \
		--Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetRGBins) \
		--ObservableRecoBins $(RecoJetRGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaJetMG.root \
		--Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--ObservableGenBins $(GenJetMGBins) \
		--ObservableRecoBins $(RecoJetMGBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)
	time ./Execute --MC MCSherpa.root --Data MCSherpa.root --Output Output/MCSherpaJetMGE.root \
		--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
		--BinningGenMin $(MGEMin) --BinningRecoMin $(MGEMin) \
		--ObservableGenBins $(GenJetMGEBins) \
		--ObservableRecoBins $(RecoJetMGEBins) \
		--BinningGenBins $(GenJetECoarseBins) \
		--BinningRecoBins $(RecoJetECoarseBins)

Execute: PrepareUnfold.cpp
	CompileRootMacro PrepareUnfold.cpp Execute \
		../../CommonCode/library/Dictionary.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .
