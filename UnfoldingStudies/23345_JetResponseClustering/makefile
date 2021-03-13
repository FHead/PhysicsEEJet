
default: TestRun

Execute: PlotJetResponse.cpp
	CompileRootMacro PlotJetResponse.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o

TestRun: Execute
	time ./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Output Data.root --MC false --JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
	time ./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Output MC.root --MC true --JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
