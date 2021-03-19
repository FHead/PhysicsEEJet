

default: TestRun

TestRun: Execute
	./Execute

Execute: Test.cpp
	rm Execute
	CompileRootMacro Test.cpp Execute -I../../CommonCode/include/
