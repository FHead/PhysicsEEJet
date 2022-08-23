
default: TestRun

TestRun: Execute
	./Execute --Input Meow.dat --Output Meow.root

Execute: Convert.cpp
	CompileRootMacro Convert.cpp Execute
