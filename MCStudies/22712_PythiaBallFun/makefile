Fraction = 1
R = 0.4

default: RunFinalPlot

RunPlot: ExecutePlot
	./ExecutePlot --Input Tree_PythiaBall0_020.root  --Output Plots_PythiaBall0_020.root
	# ./ExecutePlot --Input Tree_PythiaBall1_020.root  --Output Plots_PythiaBall1_020.root
	./ExecutePlot --Input Tree_PythiaBall5_020.root  --Output Plots_PythiaBall5_020.root
	./ExecutePlot --Input Tree_PythiaBall10_020.root --Output Plots_PythiaBall10_020.root
	# ./ExecutePlot --Input Tree_PythiaBall1_060.root  --Output Plots_PythiaBall1_060.root
	./ExecutePlot --Input Tree_PythiaBall5_060.root  --Output Plots_PythiaBall5_060.root
	./ExecutePlot --Input Tree_PythiaBall10_060.root --Output Plots_PythiaBall10_060.root
	# ./ExecutePlot --Input Tree_PythiaBall1_090.root  --Output Plots_PythiaBall1_090.root
	# /ExecutePlot --Input Tree_PythiaBall5_090.root  --Output Plots_PythiaBall5_090.root
	./ExecutePlot --Input Tree_PythiaBall10_090.root --Output Plots_PythiaBall10_090.root

RunFinalPlot: ExecuteFinalPlot
	./ExecuteFinalPlot --Input Plots_PythiaBall0_020.root,Plots_PythiaBall5_020.root,Plots_PythiaBall10_020.root \
		--Label "Pythia 91.2","Pythia 86.2 + Ball 5 (0.20)","Pythia 81.2 + Ball 10 (0.20)" \
		--Output AllPlots_MeanP020.pdf
	./ExecuteFinalPlot --Input Plots_PythiaBall0_020.root,Plots_PythiaBall10_020.root,Plots_PythiaBall10_060.root \
		--Label "Pythia 91.2","Pythia 81.2 + Ball 10 (0.20)","Pythia 81.2 + Ball 10 (0.60)" \
		--Output AllPlots_Ball10.pdf

Run2: Execute
	./Execute --Input Samples/PythiaBall0_Mean020.root  --Output Tree_PythiaBall0_020.root --Fraction $(Fraction) --R $(R)
	# ./Execute --Input Samples/PythiaBall1_Mean020.root  --Output Tree_PythiaBall1_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall5_Mean020.root  --Output Tree_PythiaBall5_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall10_Mean020.root --Output Tree_PythiaBall10_020.root --Fraction $(Fraction) --R $(R)
	# ./Execute --Input Samples/PythiaBall1_Mean060.root  --Output Tree_PythiaBall1_060.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall5_Mean060.root  --Output Tree_PythiaBall5_060.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall10_Mean060.root  --Output Tree_PythiaBall10_060.root --Fraction $(Fraction) --R $(R)
	# ./Execute --Input Samples/PythiaBall1_Mean090.root  --Output Tree_PythiaBall1_090.root --Fraction $(Fraction) --R $(R)
	# ./Execute --Input Samples/PythiaBall5_Mean090.root  --Output Tree_PythiaBall5_090.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall10_Mean090.root  --Output Tree_PythiaBall10_090.root --Fraction $(Fraction) --R $(R)

Run1: Execute
	./Execute --Input Samples/PythiaBall0_Mean020.root  --Output Tree_PythiaBall0_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall10_Mean020.root --Output Tree_PythiaBall10_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall20_Mean020.root --Output Tree_PythiaBall20_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall30_Mean020.root --Output Tree_PythiaBall30_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall40_Mean020.root --Output Tree_PythiaBall40_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall50_Mean020.root --Output Tree_PythiaBall50_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall60_Mean020.root --Output Tree_PythiaBall60_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall70_Mean020.root --Output Tree_PythiaBall70_020.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/PythiaBall80_Mean020.root --Output Tree_PythiaBall80_020.root --Fraction $(Fraction) --R $(R)

Execute: JetCorrelations.cpp
	rm -f Execute
	CompileRootMacro JetCorrelations.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

ExecutePlot: MakePlots.cpp
	rm -f ExecutePlot
	CompileRootMacro MakePlots.cpp ExecutePlot

ExecuteFinalPlot: MakeComparisonPlots.cpp
	rm -f ExecuteFinalPlot
	CompileRootMacro MakeComparisonPlots.cpp ExecuteFinalPlot
