N = 100000

default:
	echo Hello world

RunPythiaWithE: Execute
	time ./Execute --Output PureAllPythia86.root --N $(N) --EPythia 86.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia90.root --N $(N) --EPythia 89.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia89.root --N $(N) --EPythia 90.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia91.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia92.root --N $(N) --EPythia 92.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia93.root --N $(N) --EPythia 93.2 --EBall 0 --Mean 0.2 --ExcludeE false
	time ./Execute --Output PureAllPythia96.root --N $(N) --EPythia 96.2 --EBall 0 --Mean 0.2 --ExcludeE false

RunPythiaPlusBall: Execute
	time ./Execute --Output PythiaPlusBall2_Mean060.root --N $(N) --EPythia 91.2 --EBall 2 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaPlusBall5_Mean060.root --N $(N) --EPythia 91.2 --EBall 5 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaPlusBall10_Mean060.root --N $(N) --EPythia 91.2 --EBall 10 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaPlusBall20_Mean060.root --N $(N) --EPythia 91.2 --EBall 20 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaPlusBall40_Mean060.root --N $(N) --EPythia 91.2 --EBall 40 --Mean 0.6 --ExcludeE true

RunPythia: Execute
	time ./Execute --Output PurePythia90.root --N $(N) --EPythia 89.2 --EBall 0 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PurePythia89.root --N $(N) --EPythia 90.2 --EBall 0 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PurePythia91.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PurePythia92.root --N $(N) --EPythia 92.2 --EBall 0 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PurePythia93.root --N $(N) --EPythia 93.2 --EBall 0 --Mean 0.2 --ExcludeE true
	
RunPythiaOnShell: Execute
	time ./Execute --Output PurePythia91.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true

RunPythiaOnShellMeow: Execute
	time ./Execute --Output PurePythia91Meow.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true

TestRun: Execute
	time ./Execute --Output TestRunPurePythia91.root --N 10 --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true

FullRun: Execute
	time ./Execute --Output PythiaBall0_Mean020.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall10_Mean020.root --N $(N) --EPythia 81.2 --EBall 10 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall20_Mean020.root --N $(N) --EPythia 71.2 --EBall 20 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall30_Mean020.root --N $(N) --EPythia 61.2 --EBall 30 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall40_Mean020.root --N $(N) --EPythia 51.2 --EBall 40 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall50_Mean020.root --N $(N) --EPythia 41.2 --EBall 50 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall60_Mean020.root --N $(N) --EPythia 31.2 --EBall 60 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall70_Mean020.root --N $(N) --EPythia 21.2 --EBall 70 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall80_Mean020.root --N $(N) --EPythia 11.2 --EBall 80 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall90_Mean020.root --N $(N) --EPythia 0 --EBall 91.2 --Mean 0.2 --ExcludeE true

FullRun2: Execute
	time ./Execute --Output PythiaBall1_Mean020.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean020.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall1_Mean090.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean090.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall10_Mean090.root --N $(N) --EPythia 81.2 --EBall 10 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall1_Mean060.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean060.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaBall10_Mean060.root --N $(N) --EPythia 81.2 --EBall 10 --Mean 0.6 --ExcludeE true

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute Dictionary.o
