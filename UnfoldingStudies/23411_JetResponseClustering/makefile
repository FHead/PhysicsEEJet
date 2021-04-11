Fraction    = 1

DataSample    = `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"`
MCSample      = `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"`
Pythia8Sample = Pythia8Samples/PurePythia91.root
HerwigSample  = HerwigSamples/run_00/Belle_0_0.root
SherpaSample  = SherpaSamples/run_00/Belle_0_0.root

MCJEC       = ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
ResidualJEC = ../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
DataJEC     = $(MCJEC),$(ResidualJEC)


default: TestRunGenVsGenBefore TestRunGenBeforeOnly

RunGroup1: TestRun TestRunCut TestRunNoResidual TestRunNoJEC TestRunLargeThetaGap TestRunStock TestRunThetaSides TestRunPythia8 TestRunHerwig TestRunSherpa 

RunGroup2: TestRunCutSumE TestRunLargeThetaGapSumE TestRunThetaSidesSumE TestRunPythia8SumE TestRunHerwigSumE TestRunSherpaSumE TestRunCutLowerSumE TestRunCutHigherSumE

Prepare:
	rm -f Pythia8Samples SamplesData SamplesMC HerwigSamples SherpaSamples
	ln -sf ../../MCStudies/23417_PythiaWholeEvent/ Pythia8Samples
	ln -sf ../../Samples/ALEPH/ SamplesData
	ln -sf ../../Samples/ALEPHMC/ SamplesMC
	ln -sf ../../Samples/HERWIG7 HerwigSamples
	ln -sf ../../Samples/SHERPA/ SherpaSamples

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

TestRun: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoCut.root \
		--MC false --JEC $(DataJEC)
	time ./Execute --Input $(MCSample)   --Fraction $(Fraction) --Output MCNoCut.root \
		--MC true  --JEC $(MCJEC)
	
TestRunCut: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output Data.root \
		--MC false --BaselineCut true --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MC.root \
		--MC true --BaselineCut true --JEC $(MCJEC)
	
TestRunGenVsGenBefore: Execute
	time ./Execute --Input $(MCSample) --Fraction 0.05 --Output MCTGen.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgen --RecoTreeName t
	time ./Execute --Input $(MCSample) --Fraction 0.05 --Output MCTGenBefore.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgenBefore --RecoTreeName t

TestRunGenBeforeOnly: Execute
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCTGenBeforeOnly.root \
		--MC true --BaselineCut true --JEC $(MCJEC) --GenTreeName tgenBefore --RecoTreeName treco

TestRunCutSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC)

TestRunCutLowerSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLowerSumE.root \
		--MC false --BaselineCut true --RecoSumECut 81 --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLowerSumE.root \
		--MC true --BaselineCut true --GenSumECut 81 --RecoSumECut 81 --JEC $(MCJEC)

TestRunCutHigherSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataHigherSumE.root \
		--MC false --BaselineCut true --RecoSumECut 85 --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCHigherSumE.root \
		--MC true --BaselineCut true --GenSumECut 85 --RecoSumECut 85 --JEC $(MCJEC)

TestRunStock: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataStock.root \
		--MC false --BaselineCut true --UseStored true --JEC $(DataJEC)
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCStock.root \
		--MC true --BaselineCut true --UseStored true --JEC $(MCJEC)

TestRunLargeThetaGapSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLargeThetaGapSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLargeThetaGapSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535
	
TestRunLargeThetaGap:
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataLargeThetaGap.root \
		--MC false --BaselineCut true --JEC $(DataJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCLargeThetaGap.root \
		--MC true --BaselineCut true --JEC $(MCJEC) \
		--ThetaMin 0.8 --ThetaMax 2.3415926535

TestRunThetaSidesSumE: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataPositiveThetaSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCPositiveThetaSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNegativeThetaSumE.root \
		--MC false --BaselineCut true --RecoSumECut 83 --JEC $(DataJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNegativeThetaSumE.root \
		--MC true --BaselineCut true --GenSumECut 83 --RecoSumECut 83 --JEC $(MCJEC) \
		--ThetaMin 0.628319 --ThetaMax 1.570796

TestRunThetaSides: Execute
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

TestRunNoResidual: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoResidual.root \
		--MC false --BaselineCut true --JEC $(MCJEC)

TestRunNoJEC: Execute
	time ./Execute --Input $(DataSample) --Fraction $(Fraction) --Output DataNoJEC.root \
		--MC false --BaselineCut true
	time ./Execute --Input $(MCSample) --Fraction $(Fraction) --Output MCNoJEC.root \
		--MC true --BaselineCut true

TestRunPythia8SumE: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8SumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName tgen

TestRunPythia8: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8.root \
		--MC true --BaselineCut false --GenTreeName tgen

TestRunHerwigSumE: Execute
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwigSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco

TestRunHerwig: Execute
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwig.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

TestRunSherpaSumE: Execute
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpaSumE.root \
		--MC true --BaselineCut false --GenSumECut 83 --GenTreeName t --RecoTreeName treco

TestRunSherpa: Execute
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpa.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco


