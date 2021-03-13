
default: TestRun

Execute: PlotJetResponse.cpp
	CompileRootMacro PlotJetResponse.cpp Execute

TestRun: Execute
	./Execute --Input `ls SamplesData/LEP1Data1994* | tr '\n' ',' | sed "s/,$$//"` \
		--Output Data.root --MC false
	./Execute --Input `ls SamplesMC/* | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Output MC.root --MC true
