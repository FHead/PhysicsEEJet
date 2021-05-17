

default: TestRun

TestRun: Execute
	./Execute --Input output_ee_PbPbWide_0_10.pu14 --Output OutputEE_PbPbWide_0_10.root
	./Execute --Input output_ee.pu14 --Output OutputEE.root

Execute: Convert.cpp
	CompileRootMacro Convert.cpp Execute
