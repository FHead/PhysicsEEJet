Fraction = 1

default: TestRun

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

TestRun: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output Data.root --MC false \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MC.root --MC true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunNoResidual: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoResidual.root --MC false \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunNoJEC: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output DataNoJEC.root --MC false
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNoJEC.root --MC true
