
default: TestRunPlot

TestRun: Execute
	./Execute --input Samples/PythiaBall0_Mean020.root  --output PythiaBall0_Mean020.root 
	./Execute --input Samples/PythiaBall1_Mean020.root  --output PythiaBall1_Mean020.root 
	./Execute --input Samples/PythiaBall5_Mean020.root  --output PythiaBall5_Mean020.root 
	./Execute --input Samples/PythiaBall10_Mean020.root --output PythiaBall10_Mean020.root
	./Execute --input Samples/PythiaBall20_Mean020.root --output PythiaBall20_Mean020.root
	./Execute --input Samples/PythiaBall40_Mean020.root --output PythiaBall40_Mean020.root
	./Execute --input Samples/PythiaBall1_Mean060.root  --output PythiaBall1_Mean060.root 
	./Execute --input Samples/PythiaBall5_Mean060.root  --output PythiaBall5_Mean060.root 
	./Execute --input Samples/PythiaBall10_Mean060.root --output PythiaBall10_Mean060.root
	./Execute --input Samples/PythiaBall20_Mean060.root --output PythiaBall20_Mean060.root
	./Execute --input Samples/PythiaBall40_Mean060.root --output PythiaBall40_Mean060.root
	./Execute --input Samples/PythiaBall1_Mean090.root  --output PythiaBall1_Mean090.root 
	./Execute --input Samples/PythiaBall5_Mean090.root  --output PythiaBall5_Mean090.root 
	./Execute --input Samples/PythiaBall10_Mean090.root --output PythiaBall10_Mean090.root
	./Execute --input Samples/PythiaBall20_Mean090.root --output PythiaBall20_Mean090.root
	./Execute --input Samples/PythiaBall40_Mean090.root --output PythiaBall40_Mean090.root
	./Execute --input Samples/PythiaBall1_Mean020.root  --output PythiaNoBall1_Mean020.root  --noball true
	./Execute --input Samples/PythiaBall5_Mean020.root  --output PythiaNoBall5_Mean020.root  --noball true
	./Execute --input Samples/PythiaBall10_Mean020.root --output PythiaNoBall10_Mean020.root --noball true
	./Execute --input Samples/PythiaBall20_Mean020.root --output PythiaNoBall20_Mean020.root --noball true
	./Execute --input Samples/PythiaBall40_Mean020.root --output PythiaNoBall40_Mean020.root --noball true
	./Execute --input Samples/PythiaBall1_Mean060.root  --output PythiaNoBall1_Mean060.root  --noball true
	./Execute --input Samples/PythiaBall5_Mean060.root  --output PythiaNoBall5_Mean060.root  --noball true
	./Execute --input Samples/PythiaBall10_Mean060.root --output PythiaNoBall10_Mean060.root --noball true
	./Execute --input Samples/PythiaBall20_Mean060.root --output PythiaNoBall20_Mean060.root --noball true
	./Execute --input Samples/PythiaBall40_Mean060.root --output PythiaNoBall40_Mean060.root --noball true
	./Execute --input Samples/PythiaBall1_Mean090.root  --output PythiaNoBall1_Mean090.root  --noball true
	./Execute --input Samples/PythiaBall5_Mean090.root  --output PythiaNoBall5_Mean090.root  --noball true
	./Execute --input Samples/PythiaBall10_Mean090.root --output PythiaNoBall10_Mean090.root --noball true
	./Execute --input Samples/PythiaBall20_Mean090.root --output PythiaNoBall20_Mean090.root --noball true
	./Execute --input Samples/PythiaBall40_Mean090.root --output PythiaNoBall40_Mean090.root --noball true

TestRunPlot: ExecutePlot
	./ExecutePlot --ball PythiaBall0_Mean020.root --mc PythiaBall5_Mean060.root --output Ball5_060.pdf
	./ExecutePlot --ball PythiaBall0_Mean020.root --mc PythiaNoBall5_Mean060.root --output NoBall5_060.pdf

Execute: FragmentationCorrelation.cpp
	CompileRootMacro FragmentationCorrelation.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

ExecutePlot: PlotCorrelation.cpp
	CompileRootMacro PlotCorrelation.cpp ExecutePlot -I../../CommonCode/include ../../CommonCode/library/*.o
