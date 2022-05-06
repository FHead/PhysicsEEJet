


default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/UnfoldingStudies/23412_ActualUnfold/Unfolded Input

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

TestRun: Execute
	./Execute --Input Input/DataJetEVeryFineRecoBin.root --OutputBase VeryFineBin



