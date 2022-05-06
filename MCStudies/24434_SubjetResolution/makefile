
default: TestRun

Prepare:
	rm -f Input
	rm -f Dictionary_rdict.pcm
	ln -sf $(ProjectBase)/UnfoldingStudies/23514_JetResponseClustering/ Input
	ln -sf $(ProjectBase)/CommonCode/source/Dictionary_rdict.pcm

Execute: PrepareResolution.cpp
	CompileRootMacro PrepareResolution.cpp Execute -I$(ProjectBase)/CommonCode/include $(ProjectBase)/CommonCode/library/*.o

TestRun: Execute
	./Execute --Input Input/MC.root --Fraction 0.1 --Output MC.root
