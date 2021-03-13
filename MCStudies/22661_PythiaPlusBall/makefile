

TestRun: Execute
	time ./Execute --Output Pythia90_Ball0_Mean020.root --N 1000000 --EPythia 91.2 --EBall 0 --Mean 0.2
	time ./Execute --Output Pythia80_Ball10_Mean020.root --N 1000000 --EPythia 81.2 --EBall 10 --Mean 0.2
	time ./Execute --Output Pythia70_Ball20_Mean020.root --N 1000000 --EPythia 71.2 --EBall 20 --Mean 0.2
	time ./Execute --Output Pythia60_Ball30_Mean020.root --N 1000000 --EPythia 61.2 --EBall 30 --Mean 0.2
	time ./Execute --Output Pythia50_Ball40_Mean020.root --N 1000000 --EPythia 51.2 --EBall 40 --Mean 0.2
	time ./Execute --Output Pythia40_Ball50_Mean020.root --N 1000000 --EPythia 41.2 --EBall 50 --Mean 0.2
	time ./Execute --Output Pythia30_Ball60_Mean020.root --N 1000000 --EPythia 31.2 --EBall 60 --Mean 0.2
	time ./Execute --Output Pythia20_Ball70_Mean020.root --N 1000000 --EPythia 21.2 --EBall 70 --Mean 0.2
	time ./Execute --Output Pythia10_Ball80_Mean020.root --N 1000000 --EPythia 11.2 --EBall 80 --Mean 0.2
	time ./Execute --Output Pythia0_Ball90_Mean020.root --N 1000000 --EPythia 0 --EBall 91.2 --Mean 0.2

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute
