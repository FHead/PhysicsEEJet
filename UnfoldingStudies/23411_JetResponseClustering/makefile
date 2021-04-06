Fraction = 1

default: TestRun TestRunCut TestRunNoResidual TestRunNoJEC TestRunLargeThetaGap TestRunStock TestRunThetaSides TestRunPythia8 TestRunHerwig TestRunSherpa

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
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoCut.root --MC false \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNoCut.root --MC true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
	
TestRunCut: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output Data.root --MC false --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MC.root --MC true --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunStock: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataStock.root --MC false --BaselineCut true --UseStored true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCStock.root --MC true --BaselineCut true --UseStored true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunLargeThetaGap: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataLargeThetaGap.root --MC false --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt \
		--ThetaMin 0.8 --ThetaMax 2.3415926535
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCLargeThetaGap.root --MC true --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt \
		--ThetaMin 0.8 --ThetaMax 2.3415926535

TestRunThetaSides: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataPositiveTheta.root --MC false --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCPositiveTheta.root --MC true --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt \
		--ThetaMin 1.570796 --ThetaMax 2.513274
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNegativeTheta.root --MC false --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt \
		--ThetaMin 0.628319 --ThetaMax 1.570796
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNegativeTheta.root --MC true --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt \
		--ThetaMin 0.628319 --ThetaMax 1.570796

TestRunNoResidual: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoResidual.root --MC false --BaselineCut true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunNoJEC: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoJEC.root --MC false --BaselineCut true
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNoJEC.root --MC true --BaselineCut true

TestRunPythia8: Execute
	time ./Execute --Input Pythia8Samples/PurePythia91.root \
		--Fraction $(Fraction) \
		--Output MCPythia8.root --MC true --BaselineCut false

TestRunHerwig: Execute
	time ./Execute --Input HerwigSamples/run_00/Belle_0_0.root \
		--Fraction $(Fraction) \
		--Output MCHerwig.root --MC true --BaselineCut false \
		--GenTreeName t --RecoTreeName treco

TestRunSherpa: Execute
	time ./Execute --Input SherpaSamples/run_00/Belle_0_0.root \
		--Fraction $(Fraction) \
		--Output MCSherpa.root --MC true --BaselineCut false \
		--GenTreeName t --RecoTreeName treco

