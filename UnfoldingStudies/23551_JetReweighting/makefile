
default: TestRun

Prepare:
	ln -sf ../23412_ActualUnfold/Unfolded/ Input

Execute: DeriveReweighting.cpp
	CompileRootMacro DeriveReweighting.cpp Execute

TestRun: Execute
	./Execute --DataInput Input/DataJetENominal.root --MCInput Input/DataJetENominal.root \
		--DataName HUnfoldedBayes30 --MCName HMCTruth



