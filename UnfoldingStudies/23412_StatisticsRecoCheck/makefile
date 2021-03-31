N = 100

default: TestRun

TestRun: Execute
	./Execute --Input `ls Input/ToyDataJetEStatistics_1*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetEStatistics.pdf
	./Execute --Input `ls Input/ToyDataJetZGStatistics_1*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetZGStatistics.pdf
	./Execute --Input `ls Input/ToyDataJetRGStatistics_1*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetRGStatistics.pdf

Execute: ValidateStatistics.cpp
	CompileRootMacro ValidateStatistics.cpp Execute
