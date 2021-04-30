N = 1000

default: TestRun

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded/ Input

TestRun: Execute
	./Execute --Input `ls Input/ToyDataJetEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetEStatistics.pdf --IgnoreBin 10 --Method UnfoldedBayes30 --Observable "Jet E"
	./Execute --Input `ls Input/ToyDataLeadingDiJetEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataLeadingDiJetEStatistics.pdf --IgnoreBin 1 --Method UnfoldedBayes25 --Observable "Leading Dijet E"
	./Execute --Input `ls Input/ToyDataLeadingDiJetSumEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataLeadingDiJetSumEStatistics.pdf --IgnoreBin 1 --Method UnfoldedBayes25 --Observable "Leading Dijet SumE"
	./Execute --Input `ls Input/ToyDataJetZGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetZGStatistics.pdf --IgnoreBin 20 --Method UnfoldedBayes25 --Observable "Jet z_{G}"
	./Execute --Input `ls Input/ToyDataJetRGStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetRGStatistics.pdf --IgnoreBin 22 --Method UnfoldedBayes25 --Observable "Jet R_{G}"
	./Execute --Input `ls Input/ToyDataJetMEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetMEStatistics.pdf --IgnoreBin 22 --Method UnfoldedBayes25 --Observable "Jet M/E"
	./Execute --Input `ls Input/ToyDataJetMGEStatistics_*.root | head -n $(N) | tr '\n' ',' | sed "s/,$$//"` \
		--Output ToyDataJetMGEStatistics.pdf --IgnoreBin 24 --Method UnfoldedBayes25 --Observable "Jet M_{G}/E"

Execute: ValidateStatistics.cpp
	CompileRootMacro ValidateStatistics.cpp Execute
