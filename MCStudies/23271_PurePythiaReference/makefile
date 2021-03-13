

default: TestRunPlot

TestRun: Execute
	./Execute --input Samples/PurePythia89.root --output PurePythia89.root --noball true --r 0.4
	./Execute --input Samples/PurePythia90.root --output PurePythia90.root --noball true --r 0.4
	./Execute --input Samples/PurePythia91.root --output PurePythia91.root --noball true --r 0.4
	./Execute --input Samples/PurePythia92.root --output PurePythia92.root --noball true --r 0.4
	./Execute --input Samples/PurePythia93.root --output PurePythia93.root --noball true --r 0.4

TestRunPlot: ExecutePlot
	./ExecutePlot \
		--input PurePythia89.root,PurePythia90.root,PurePythia91.root,PurePythia92.root,PurePythia93.root \
		--output PurePythiaPlots.pdf \
		--label 89,90,91,92,93

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o

ExecutePlot: MakePlots.cpp
	CompileRootMacro MakePlots.cpp ExecutePlot

