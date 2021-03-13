N = 100000

default:
	echo Hello world

TestRun: Execute
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

TestRun2: Execute
	time ./Execute --Output PythiaBall1_Mean020.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean020.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.2 --ExcludeE true
	time ./Execute --Output PythiaBall1_Mean090.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean090.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall10_Mean090.root --N $(N) --EPythia 81.2 --EBall 10 --Mean 0.9 --ExcludeE true
	time ./Execute --Output PythiaBall1_Mean060.root --N $(N) --EPythia 90.2 --EBall 1 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaBall5_Mean060.root --N $(N) --EPythia 86.2 --EBall 5 --Mean 0.6 --ExcludeE true
	time ./Execute --Output PythiaBall10_Mean060.root --N $(N) --EPythia 81.2 --EBall 10 --Mean 0.6 --ExcludeE true

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute
