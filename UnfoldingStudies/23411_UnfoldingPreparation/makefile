
Observables           = JetE,LeadingDiJetE,LeadingDiJetSumE,JetZG,JetRG,JetMG,JetMGE,JetM,JetME,JetZG2,JetRG2,JetMG2,JetMGE2
LeadingObservables    = LeadingDiJetE,LeadingDiJetSumE
# Observables = LeadingJetE

default: Preparation23514

RunThrust: ThrustNominalRun ThrustNoCutRun

RunNominal: Preparation23514 DataNominalRun FakeDataNominalRun DataSumERun MCNominalRun \
	MCNoJECRun DataJECRunHalf DataNoResidualRun \
	DataJECRun DataJERRun \
	DataSJSmearRun \
	MCSumERun \
	DataLargeThetaGapRun MCLargeThetaGapRun DataThetaSideRun MCThetaSideRun MCExtra \
	DataFlooredRun DataTighterRun FakeFakeRun \
	NoNeutralRun DataFineBinRun DataVeryFineBinRun MCGenReweightRun DataGenReweightRun

MCExtra: MCPythia6 MCPythia8 MCHerwig MCSherpa MCHerwig715 MCPyquen MCPyquenStrong MCVincia1 MCVincia2 MCLeading

RunAll: Preparation23514 RunThrust RunNominal LowEInvestigation

Preparation:
	ln -sf ../23411_JetResponseClustering/*root .
	mkdir -p Output/

Preparation23514:
	ln -sf ../23514_JetResponseClustering/*root .
	mkdir -p Output/

ThrustNominalRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--Prefix Data --Suffix Nominal \
		--Observables Thrust | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--Prefix Data --Suffix Uniform \
		--Observables ThrustUniform | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--Prefix MC --Suffix Nominal \
		--Observables Thrust | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--Prefix MC --Suffix Uniform \
		--Observables ThrustUniform | grep ^time`

ThrustNoCutRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCNoCut.root --Data DataNoCut.root \
		--Prefix DataNoCut --Suffix Nominal \
		--Observables Thrust | grep ^time`
	eval `./ExecutePreset --MC MCNoCut.root --Data DataNoCut.root \
		--Prefix DataNoCut --Suffix Uniform \
		--Observables ThrustUniform | grep ^time`
	eval `./ExecutePreset --MC MCNoCut.root --Data MCNoCut.root \
		--Prefix MCNoCut --Suffix Nominal \
		--Observables Thrust | grep ^time`
	eval `./ExecutePreset --MC MCNoCut.root --Data MCNoCut.root \
		--Prefix MCNoCut --Suffix Uniform \
		--Observables ThrustUniform | grep ^time`

DataThetaSideRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCPositiveTheta.root --Data DataPositiveTheta.root \
		--MCSumE MCPositiveThetaSumE.root --DataSumE DataPositiveThetaSumE.root \
		--Prefix Data --Suffix PositiveTheta --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCNegativeTheta.root --Data DataNegativeTheta.root \
		--MCSumE MCNegativeThetaSumE.root --DataSumE DataNegativeThetaSumE.root \
		--Prefix Data --Suffix NegativeTheta --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataLargeThetaGapRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCLargeThetaGap.root --Data DataLargeThetaGap.root \
		--MCSumE MCLargeThetaGapSumE.root --DataSumE DataLargeThetaGapSumE.root \
		--Prefix Data --Suffix LargeThetaGap --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

MCThetaSideRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCPositiveTheta.root --Data MCPositiveTheta.root \
		--MCSumE MCPositiveThetaSumE.root --DataSumE MCPositiveThetaSumE.root \
		--Prefix MC --Suffix PositiveTheta --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCNegativeTheta.root --Data MCNegativeTheta.root \
		--MCSumE MCNegativeThetaSumE.root --DataSumE MCNegativeThetaSumE.root \
		--Prefix MC --Suffix NegativeTheta --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

MCLargeThetaGapRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCLargeThetaGap.root --Data MCLargeThetaGap.root \
		--MCSumE MCLargeThetaGapSumE.root --DataSumE DataLargeThetaGapSumE.root \
		--Prefix MC --Suffix LargeThetaGap --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

DataNominalRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix Nominal --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataGenReweightRun: Execute ExecutePreset
	# eval `./ExecutePreset --MC MC.root --Data Data.root \
	# 	--MCSumE MCSumE.root --DataSumE DataSumE.root \
	# 	--Prefix Data --Suffix GenReweightN05Test --Shift 0.0 --Smear 1.025 \
	# 	--Observables $(Observables) --GenReweight N05Test | grep ^time`
	# eval `./ExecutePreset --MC MC.root --Data Data.root \
	# 	--MCSumE MCSumE.root --DataSumE DataSumE.root \
	# 	--Prefix Data --Suffix GenReweightN10Test --Shift 0.0 --Smear 1.025 \
	# 	--Observables $(Observables) --GenReweight N10Test | grep ^time`
	# eval `./ExecutePreset --MC MC.root --Data Data.root \
	# 	--MCSumE MCSumE.root --DataSumE DataSumE.root \
	# 	--Prefix Data --Suffix GenReweightN15Test --Shift 0.0 --Smear 1.025 \
	# 	--Observables $(Observables) --GenReweight N15Test | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix GenReweightZGDown --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) --GenReweight ZGDown | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix GenReweightZGUp --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) --GenReweight ZGUp | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix GenReweightRGDown --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) --GenReweight RGDown | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix GenReweightRGUp --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) --GenReweight RGUp | grep ^time`

DataFineBinRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix FineRecoBin --Shift 0.0 --Smear 1.025 \
		--FineRecoBins true \
		--Observables $(Observables) | grep ^time`

DataVeryFineBinRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix VeryFineRecoBin --Shift 0.0 --Smear 1.025 \
		--VeryFineRecoBins true \
		--Observables $(Observables) | grep ^time`

NoNeutralRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCNoNeutral.root --Data DataNoNeutral.root \
		--MCSumE MCNoNeutralSumE.root --DataSumE DataNoNeutralSumE.root \
		--Prefix Data --Suffix NoNeutral --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCNoNeutral.root --Data MCNoNeutral.root \
		--MCSumE MCNoNeutralSumE.root --DataSumE MCNoNeutralSumE.root \
		--Prefix MC --Suffix NoNeutral --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

FakeDataNominalRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data FakeData.root \
		--MCSumE MCSumE.root --DataSumE FakeDataSumE.root \
		--Prefix FakeData --Suffix Nominal --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

FakeFakeRun: Execute ExecutePreset
	eval `./ExecutePreset --MC FakeData.root --Data FakeData.root \
		--MCSumE FakeDataSumE.root --DataSumE FakeDataSumE.root \
		--Prefix FakeFake --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

DataTighterRun: Execute ExecutePreset
	# Check SumE
	eval `./ExecutePreset --MC MCTighterCut.root --Data DataTighterCut.root \
		--MCSumE MCTighterCutSumE.root --Data DataTighterCutSumE.root \
		--Prefix Data --Suffix Tighter --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataFlooredRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix Floored --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) --Flooring true | grep ^time`

DataSumERun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCLowerSumE.root --DataSumE DataLowerSumE.root \
		--Prefix Data --Suffix LowerSumE --Shift 0.0 --Smear 1.025 \
		--Observables $(LeadingObservables) | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCHigherSumE.root --DataSumE DataHigherSumE.root \
		--Prefix Data --Suffix HigherSumE --Shift 0.0 --Smear 1.025 \
		--Observables $(LeadingObservables) | grep ^time`

MCSumERun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCSmearedSumE.root --DataSumE MCSmearedSumE.root \
		--Prefix MC --Suffix SmearedSumE --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

DataJECRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JECUp --Shift 1.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JECDown --Shift -1.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataJECRunHalf: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JECHalfUp --Shift 0.5 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JECHalfDown --Shift -0.5 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataJERRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JERUp --Shift 0.0 --Smear 1.05 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix JERDown --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

DataSJSmearRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MCSJSmear.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix SJSmear --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

DataNoResidualRun: Execute ExecutePreset
	# Check SumE
	eval `./ExecutePreset --MC MC.root --Data DataNoResidual.root \
		--MCSumE MCSumE.root --DataSumE DataNoResidualSumE.root \
		--Prefix Data --Suffix NoResidual --Shift 0.0 --Smear 1.025 \
		--Observables $(Observables) | grep ^time`

MCNominalRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCSumE.root --DataSumE MCSumE.root \
		--Prefix MC --Suffix Nominal --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

MCGenReweightRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCSumE.root --DataSumE MCSumE.root \
		--Prefix MC --Suffix GenReweightN05Test --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) --GenReweight N05Test | grep ^time`

MCNoJECRun: Execute ExecutePreset
	# Check SumE
	eval `./ExecutePreset --MC MCNoJEC.root --Data MCNoJEC.root \
		--MCSumE MCNoJECSumE.root --DataSumE MCNoJECSumE.root \
		--Prefix MC --Suffix NoJEC --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

MCLeading: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCLeading.root --DataSumE MCLeading.root \
		--Prefix MCTrue --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCPythia6: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCPythia6SumE.root --DataSumE MCPythia6SumE.root \
		--Prefix MCPythia6 --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`

MCPythia8: Execute ExecutePreset
	eval `./ExecutePreset --MC MCPythia8.root --Data MCPythia8.root \
		--MCSumE MCPythia8SumE.root --DataSumE MCPythia8SumE.root \
		--Prefix MCPythia8 --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCPythia8.root --Data MCPythia8.root \
		--MCSumE MCPythia8Leading.root --DataSumE MCPythia8Leading.root \
		--Prefix MCPythia8True --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCHerwig: Execute ExecutePreset
	eval `./ExecutePreset --MC MCHerwig.root --Data MCHerwig.root \
		--MCSumE MCHerwigSumE.root --DataSumE MCHerwigSumE.root \
		--Prefix MCHerwig --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCHerwig.root --Data MCHerwig.root \
		--MCSumE MCHerwigLeading.root --DataSumE MCHerwigLeading.root \
		--Prefix MCHerwigTrue --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCSherpa: Execute ExecutePreset
	eval `./ExecutePreset --MC MCSherpa.root --Data MCSherpa.root \
		--MCSumE MCSherpaSumE.root --DataSumE MCSherpaSumE.root \
		--Prefix MCSherpa --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCSherpa.root --Data MCSherpa.root \
		--MCSumE MCSherpaLeading.root --DataSumE MCSherpaLeading.root \
		--Prefix MCSherpaTrue --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCHerwig715: Execute ExecutePreset
	eval `./ExecutePreset --MC MCHerwig715.root --Data MCHerwig715.root \
		--MCSumE MCHerwig715SumE.root --DataSumE MCHerwig715SumE.root \
		--Prefix MCHerwig715 --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCHerwig715.root --Data MCHerwig715.root \
		--MCSumE MCHerwig715Leading.root --DataSumE MCHerwig715Leading.root \
		--Prefix MCHerwig715True --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCPyquen: Execute ExecutePreset
	eval `./ExecutePreset --MC MCPyquen.root --Data MCPyquen.root \
		--MCSumE MCPyquenSumE.root --DataSumE MCPyquenSumE.root \
		--Prefix MCPyquen --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCPyquen.root --Data MCPyquen.root \
		--MCSumE MCPyquenLeading.root --DataSumE MCPyquenLeading.root \
		--Prefix MCPyquenTrue --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCPyquenStrong: Execute ExecutePreset
	eval `./ExecutePreset --MC MCPyquenStrong.root --Data MCPyquenStrong.root \
		--MCSumE MCPyquenStrongSumE.root --DataSumE MCPyquenStrongSumE.root \
		--Prefix MCPyquenStrong --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCPyquenStrong.root --Data MCPyquenStrong.root \
		--MCSumE MCPyquenStrongLeading.root --DataSumE MCPyquenStrongLeading.root \
		--Prefix MCPyquenStrongTrue --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCVincia1: Execute ExecutePreset
	eval `./ExecutePreset --MC MCVincia1.root --Data MCVincia1.root \
		--MCSumE MCVincia1SumE.root --DataSumE MCVincia1SumE.root \
		--Prefix MCVincia1 --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCVincia1.root --Data MCVincia1.root \
		--MCSumE MCVincia1Leading.root --DataSumE MCVincia1Leading.root \
		--Prefix MCVincia1True --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

MCVincia2: Execute ExecutePreset
	eval `./ExecutePreset --MC MCVincia2.root --Data MCVincia2.root \
		--MCSumE MCVincia2SumE.root --DataSumE MCVincia2SumE.root \
		--Prefix MCVincia2 --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(Observables) | grep ^time`
	eval `./ExecutePreset --MC MCVincia2.root --Data MCVincia2.root \
		--MCSumE MCVincia2Leading.root --DataSumE MCVincia2Leading.root \
		--Prefix MCVincia2True --Suffix "" --Shift 0.0 --Smear 1.00 \
		--Observables $(LeadingObservables) | grep ^time`

LowEInvestigation: Execute
	echo "Uncomment to resurrect this check"
	# time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetMGELowECut.root \
	# 	--Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
	# 	--BinningGenMin 2 --BinningRecoMin 2 \
	# 	--ObservableGenBins $(GenJetMGEBins) \
	# 	--ObservableRecoBins $(RecoJetMGEBins) \
	# 	--BinningGenBins $(GenJetECoarseBins) \
	# 	--BinningRecoBins $(RecoJetECoarseBins)
	# time ./Execute --MC MC.root --Data MC.root --Output Output/MCJetMELowECut.root \
	# 	--Observable JetME --ObservableIndex 0 --Binning JetE --BinningIndex -1 \
	# 	--BinningGenMin 2 --BinningRecoMin 2 \
	# 	--ObservableGenBins $(GenJetMEBins) \
	# 	--ObservableRecoBins $(RecoJetMEBins) \
	# 	--BinningGenBins $(GenJetECoarseBins) \
	# 	--BinningRecoBins $(RecoJetECoarseBins)

DebugRun: Execute ExecutePreset
	eval `./ExecutePreset --MC MC.root --Data MC.root \
		--MCSumE MCSumE.root --DataSumE MCSumE.root \
		--Prefix MC --Suffix Nominal --Shift 0.0 --Smear 1.00 \
		--Observables JetZG | grep ^time`
	eval `./ExecutePreset --MC MC.root --Data Data.root \
		--MCSumE MCSumE.root --DataSumE DataSumE.root \
		--Prefix Data --Suffix Nominal --Shift 0.0 --Smear 1.025 \
		--Observables JetZG | grep ^time`

Execute: PrepareUnfold.cpp
	CompileRootMacro PrepareUnfold.cpp Execute \
		../../CommonCode/library/Dictionary.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

ExecutePreset: RunPreset.cpp
	CompileRootMacro RunPreset.cpp ExecutePreset
