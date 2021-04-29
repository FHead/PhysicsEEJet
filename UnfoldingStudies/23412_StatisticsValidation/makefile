N = 1000

default: TestRun

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded/ Input

TestRun: Execute
	./Execute --Input `ls Input/ToyDataJetEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetEStatistics.pdf --IgnoreBin 10 --Method UnfoldedBayes17
	./Execute --Input `ls Input/ToyDataLeadingDiJetEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataLeadingDiJetEStatistics.pdf --IgnoreBin 10 --Method UnfoldedBayes7
	./Execute --Input `ls Input/ToyDataLeadingDiJetSumEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataLeadingDiJetSumEStatistics.pdf --IgnoreBin 10 --Method UnfoldedBayes15
	./Execute --Input `ls Input/ToyDataJetZGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetZGStatistics.pdf --IgnoreBin 18 --Method UnfoldedBayes17
	./Execute --Input `ls Input/ToyDataJetRGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetRGStatistics.pdf --IgnoreBin 24 --Method UnfoldedBayes18
	./Execute --Input `ls Input/ToyDataJetMEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetMEStatistics.pdf --IgnoreBin 24 --Method UnfoldedBayes17
	./Execute --Input `ls Input/ToyDataJetMGEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetMGEStatistics.pdf --IgnoreBin 24 --Method UnfoldedBayes16

Execute: ValidateStatistics.cpp
	CompileRootMacro ValidateStatistics.cpp Execute
