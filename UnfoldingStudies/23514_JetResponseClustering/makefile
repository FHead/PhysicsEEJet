Fraction             = 1.00

DataSample           = `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"`
MCSample             = `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"`
Pythia8Sample        = Pythia8Samples/PurePythia91.root
HerwigSample         = HerwigSamples/run_00/Belle_0_0.root,HerwigSamples/run_01/Belle_0_0.root
Herwig715Sample      = Herwig715Samples/run_00/Belle_0_0.root
SherpaSample         = SherpaSamples/run_00/Belle_0_0.root
PyquenSample         = PyquenSamples/OutputEE.root
PyquenStrongSample   = PyquenSamples/OutputEE_PbPbWide_0_10.root
Vincia1Sample        = VinciaSamples/Pythia91Shower1.root
Vincia2Sample        = VinciaSamples/Pythia91Shower2.root
JetScapeSample       = JetScapeSamples/JetScapeEEHadrons.root
JetScapeBypassSample = JetScapeSamples/JetScapeEEHadronsBypass.root
JetScapeSmashSample  = JetScapeSamples/JetScapeEEHadronsSmash.root
JetScapeLHESample    = JetScapeSamples/JetScapeEEHadronsLHE.root

MCJEC       = ../../JetCorrection/23474_MC/JECR4.txt
ResidualJEC = ../../JetCorrection/23475_DataRel/JECRelativeResidualR4.txt,../../JetCorrection/23475_DataAbs/JECResidualR4.txt
DataJEC     = $(MCJEC),$(ResidualJEC)

default: DebugRun
# RunGenVsGenBefore RunGenBeforeOnly

RunGroup1: RunCut RunNoCut RunTighterCut RunNoResidual RunNoJEC RunLargeThetaGap RunStock RunThetaSides RunPythia8 RunHerwig RunSherpa RunHerwig715 RunPyquen RunVincia RunSJSmear

RunGroup2: RunCutSumE RunCutSmearedSumE RunTighterCutSumE RunNoJECSumE RunLargeThetaGapSumE RunThetaSidesSumE RunPythia6SumE RunPythia8SumE RunHerwigSumE RunSherpaSumE RunCutLowerSumE RunCutHigherSumE RunHerwig715SumE RunPyquenSumE RunVinciaSumE

RunGroup3: RunMultiplicity

RunGroup4: RunJetScape

Prepare:
	rm -f Pythia8Samples SamplesData SamplesMC HerwigSamples SherpaSamples
	ln -sf ../../MCStudies/23417_PythiaWholeEvent/ Pythia8Samples
	ln -sf ../../Samples/ALEPH/ SamplesData
	ln -sf ../../Samples/ALEPHMC/ SamplesMC
	ln -sf ../../Samples/HERWIG7 HerwigSamples
	ln -sf ../../Samples/HERWIG715 Herwig715Samples
	ln -sf ../../Samples/SHERPA/ SherpaSamples
	ln -sf ../../MCStudies/23451_PU14ToALEPHTree/ PyquenSamples
	ln -sf ../../MCStudies/23741_VinciaPythiaFullEvent/ VinciaSamples

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o -g 
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

RunNoCut: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoCut.root \
		--MC false --JEC $(DataJEC)
	time ./Execute --Input $(MCSample)   --Fraction $(Fraction) --Output MCNoCut.root \
		--MC true  --JEC $(MCJEC)
	
RunCut: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output Data.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --DoAuxiliary true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MC.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --DoAuxiliary true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output FakeData.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --DoAuxiliary true

RunSJSmear: Execute
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCSJSmear.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --DoAuxiliary true --DoSJSmear true

RunNoNeutral: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoNeutral.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --IgnoreNeutral true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNoNeutral.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --IgnoreNeutral true
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoNeutralSumE.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --IgnoreNeutral true --RecoSumECut 83 --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNoNeutralSumE.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --IgnoreNeutral true --RecoSumECut 83 --GenSumECut 83 --DoHybridSumE true
	
RunTighterCut: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataTighterCut.root \
		--MC false --BaselineCut true --TighterChargedHadronCut true --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCTighterCut.root \
		--MC true --BaselineCut true --TighterChargedHadronCut true --JEC $(MCJEC)
	
RunTighterCutSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataTighterCutSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --TighterChargedHadronCut true --JEC $(DataJEC) --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCTighterCutSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --TighterChargedHadronCut true --JEC $(MCJEC) --DoHybridSumE true
	
RunGenVsGenBefore: Execute
	time ./Execute --Input $(MCSample) --Fraction 0.05 --Output MCTGen.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgen --RecoTreeName t
	time ./Execute --Input $(MCSample) --Fraction 0.05 --Output MCTGenBefore.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgenBefore --RecoTreeName t

RunGenBeforeOnly: Execute
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCTGenBeforeOnly.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgenBefore --RecoTreeName treco

RunCutSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output FakeDataSumE.root \
		--MC true --BaselineCut true --RecoSumECut 83 --JEC $(MCJEC) --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) --DoHybridSumE true

RunCutLowerSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLowerSumE.root \
		--MC false --BaselineCut true --RecoSumECut 81 --JEC $(DataJEC) --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLowerSumE.root \
		--MC true --BaselineCut true --GenSumECut 81 --RecoSumECut 81 --JEC $(MCJEC) --DoHybridSumE true

RunCutHigherSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataHigherSumE.root \
		--MC false --BaselineCut true --RecoSumECut 85 --JEC $(DataJEC) --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCHigherSumE.root \
		--MC true --BaselineCut true --GenSumECut 85 --RecoSumECut 85 --JEC $(MCJEC) --DoHybridSumE true

RunCutSmearedSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataSmearedSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) --DoSumESmear true --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCSmearedSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) --DoSumESmear true --DoHybridSumE true

RunStock: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataStock.root \
		--MC false --BaselineCut true --UseStored true --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCStock.root \
		--MC true --BaselineCut true --UseStored true --JEC $(MCJEC)

RunLargeThetaGapSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLargeThetaGapSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535 --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLargeThetaGapSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535 --DoHybridSumE true
	
RunLargeThetaGap:
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLargeThetaGap.root \
		--MC false --BaselineCut true --JEC $(DataJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLargeThetaGap.root \
		--MC true --BaselineCut true --JEC $(MCJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535

RunThetaSidesSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataPositiveThetaSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274 --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCPositiveThetaSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274 --DoHybridSumE true
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNegativeThetaSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796 --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNegativeThetaSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796 --DoHybridSumE true

RunThetaSides: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataPositiveTheta.root \
		--MC false --BaselineCut true --JEC $(DataJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCPositiveTheta.root \
		--MC true --BaselineCut true --JEC $(MCJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNegativeTheta.root \
		--MC false --BaselineCut true --JEC $(DataJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNegativeTheta.root \
		--MC true --BaselineCut true --JEC $(MCJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796

RunNoResidual: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoResidual.root \
		--MC false --BaselineCut true --JEC $(MCJEC)
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoResidualSumE.root \
		--MC false --BaselineCut true --JEC $(MCJEC) --RecoSumECut 83 --DoHyrbidSumE true

RunNoJEC: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoJEC.root \
		--MC false --BaselineCut true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNoJEC.root \
		--MC true --BaselineCut true

RunNoJECSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoJECSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNoJECSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --DoHybridSumE true

RunPythia6SumE: Execute
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCPythia6SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgenBefore --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCPythia6RecoSumE.root \
		--MC true --BaselineCut false --RecoSumECut 83 --GenTreeName tgenBefore --DoHybridSumE true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgenBefore --RecoTreeName treco --DoHybridSumE true

RunPythia8SumE: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --DoHybridSumE true
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8Leading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true

RunPythia8: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8.root \
		--MC true --BaselineCut false --GenTreeName tgen

RunHerwigSumE: Execute
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwigSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwigLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName t --RecoTreeName treco --DoHybridSumE true

RunHerwig: Execute
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwig.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunHerwig715SumE: Execute
	time ./Execute --Input $(Herwig715Sample) --Fraction $(Fraction) --Output MCHerwig715SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(Herwig715Sample) --Fraction $(Fraction) --Output MCHerwig715Leading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName t --RecoTreeName treco --DoHybridSumE true

RunHerwig715: Execute
	time ./Execute --Input $(Herwig715Sample) --Fraction $(Fraction) --Output MCHerwig715.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunSherpaSumE: Execute
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpaSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpaLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName t --RecoTreeName treco --DoHybridSumE true

RunSherpa: Execute
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpa.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunPyquenSumE: Execute
	time ./Execute --Input $(PyquenStrongSample) --Fraction $(Fraction) --Output MCPyquenStrongSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(PyquenStrongSample) --Fraction $(Fraction) --Output MCPyquenStrongLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(PyquenSample) --Fraction $(Fraction) --Output MCPyquenSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(PyquenSample) --Fraction $(Fraction) --Output MCPyquenLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName t --RecoTreeName treco --DoHybridSumE true

RunPyquen: Execute
	time ./Execute --Input $(PyquenStrongSample) --Fraction $(Fraction) --Output MCPyquenStrong.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco
	time ./Execute --Input $(PyquenSample) --Fraction $(Fraction) --Output MCPyquen.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunVinciaSumE: Execute
	time ./Execute --Input $(Vincia1Sample) --Fraction $(Fraction) --Output MCVincia1SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(Vincia1Sample) --Fraction $(Fraction) --Output MCVincia1Leading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true
	time ./Execute --Input $(Vincia2Sample) --Fraction $(Fraction) --Output MCVincia2SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(Vincia2Sample) --Fraction $(Fraction) --Output MCVincia2Leading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true

RunVincia: Execute
	time ./Execute --Input $(Vincia1Sample) --Fraction $(Fraction) --Output MCVincia1.root \
		--MC true --BaselineCut false --GenTreeName tgen --RecoTreeName treco
	time ./Execute --Input $(Vincia2Sample) --Fraction $(Fraction) --Output MCVincia2.root \
		--MC true --BaselineCut false --GenTreeName tgen --RecoTreeName treco

RunMultiplicity: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLowN.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --RecoMultiplicityMin 0 --RecoMultiplicityMax 1000
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataMidN.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --RecoMultiplicityMin 0 --RecoMultiplicityMax 1000
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataHighN.root \
		--MC false --BaselineCut true --JEC $(DataJEC) --RecoMultiplicityMin 0 --RecoMultiplicityMax 1000

RunJetScape: Execute
	time ./Execute --Input $(JetScapeSample) --Fraction $(Fraction) --Output MCJetScape.root \
		--MC true --UseStored false --BaselineCut false --GenTreeName tgen --RecoTreeName t
	time ./Execute --Input $(JetScapeSample) --Fraction $(Fraction) --Output MCJetScapeSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(JetScapeSample) --Fraction $(Fraction) --Output MCJetScapeLeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true
	# time ./Execute --Input $(JetScapeBypassSample) --Fraction $(Fraction) --Output MCJetScapeBypass.root \
	# 	--MC true --UseStored false --BaselineCut false --GenTreeName tgen --RecoTreeName t
	# time ./Execute --Input $(JetScapeBypassSample) --Fraction $(Fraction) --Output MCJetScapeBypassSumE.root \
	# 	--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	# time ./Execute --Input $(JetScapeBypassSample) --Fraction $(Fraction) --Output MCJetScapeBypassLeading.root \
	# 	--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true
	# time ./Execute --Input $(JetScapeSmashSample) --Fraction $(Fraction) --Output MCJetScapeSmash.root \
	# 	--MC true --UseStored false --BaselineCut false --GenTreeName tgen --RecoTreeName t
	# time ./Execute --Input $(JetScapeSmashSample) --Fraction $(Fraction) --Output MCJetScapeSmashSumE.root \
	# 	--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	# time ./Execute --Input $(JetScapeSmashSample) --Fraction $(Fraction) --Output MCJetScapeSmashLeading.root \
	# 	--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true
	time ./Execute --Input $(JetScapeLHESample) --Fraction $(Fraction) --Output MCJetScapeLHE.root \
		--MC true --UseStored false --BaselineCut false --GenTreeName tgen --RecoTreeName t
	time ./Execute --Input $(JetScapeLHESample) --Fraction $(Fraction) --Output MCJetScapeLHESumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen --RecoTreeName treco --DoHybridSumE true
	time ./Execute --Input $(JetScapeLHESample) --Fraction $(Fraction) --Output MCJetScapeLHELeading.root \
		--MC true --BaselineCut false --CheckLeadingGenDiJet true --GenTreeName tgen --DoHybridSumE true

DebugRun: Execute
	time ./Execute --Input $(MCSample) --Fraction 0.02 --Output MCDebug.root \
		--MC true --BaselineCut true --JEC $(MCJEC)
