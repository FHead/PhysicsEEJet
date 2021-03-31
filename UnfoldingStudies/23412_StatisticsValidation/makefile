N = 1000

default: TestRun

TestRun: Execute
	./Execute --Input `ls Input/ToyDataJetEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetEStatistics.pdf --IgnoreBin 10 --Method UnfoldedBayes25
	./Execute --Input `ls Input/ToyDataJetZGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetZGStatistics.pdf --IgnoreBin 18 --Method UnfoldedBayes25
	./Execute --Input `ls Input/ToyDataJetRGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetRGStatistics.pdf --IgnoreBin 24 --Method UnfoldedBayes25

Execute: ValidateStatistics.cpp
	CompileRootMacro ValidateStatistics.cpp Execute
