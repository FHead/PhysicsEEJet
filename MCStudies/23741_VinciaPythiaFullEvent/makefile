N = 100000

default:
	echo Hello world

RunPythiaOnShell: Execute
	time ./Execute --Output Pythia91Shower1.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true --Shower 1
	time ./Execute --Output Pythia91Shower2.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true --Shower 2

TestRun: Execute
	time ./Execute --Output TestRunPurePythia91.root --N 10 --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute Dictionary.o
