Fraction = 1.0

default: TestRun TestRunCut TestRunNoResidual TestRunNoJEC

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute -g \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

DebugRun: Execute
	# time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
	# 	--Fraction 0.02 --MatchingScheme 0 \
	# 	--Output MCDebug0.root --MC true \
	# 	--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
	# time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
	# 	--Fraction 0.02 --MatchingScheme 1 \
	# 	--Output MCDebug1.root --MC true \
	# 	--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction 0.02 --MatchingScheme 2 \
		--Output MCDebug2.root --MC true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRun: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoCut.root --MC false \
		--MatchingScheme 2 \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNoCut.root --MC true \
		--MatchingScheme 2 \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
	
TestRunCut: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output Data.root --MC false --BaselineCut true \
		--MatchingScheme 2 \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MC.root --MC true --BaselineCut true \
		--MatchingScheme 2 \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunNoResidual: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoResidual.root --MC false --BaselineCut true \
		--MatchingScheme 2 \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunNoJEC: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--MatchingScheme 2 \
		--Output DataNoJEC.root --MC false --BaselineCut true
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--MatchingScheme 2 \
		--Output MCNoJEC.root --MC true --BaselineCut true


