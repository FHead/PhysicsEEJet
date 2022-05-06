
default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/UnfoldingStudies/23514_JetResponseClustering/ Input

Execute: DeriveWeight.cpp
	CompileRootMacro DeriveWeight.cpp Execute

TestRun: Execute
	./Execute --Input Input/MCPythia8.root --Base Input/MC.root --Output Pythia8Weight.pdf
	./Execute --Input Input/MCHerwig.root --Base Input/MC.root --Output HerwigWeight.pdf
