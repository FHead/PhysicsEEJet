

default: Systematics FinalPlot

RunAll: JetClustering UnfoldPreparation NominalUnfold MCIterationScan DataIterationScan Systematics FinalPlot

JetClustering:
	(cd 23411_JetResponseClustering/ && make Prepare TestRun TestRunCut TestRunNoResidual TestRunNoJEC TestRunLargeThetaGap TestRunThetaSides TestRunStock TestRunPythia8 TestRunHerwig TestRunSherpa)

UnfoldPreparation:
	(cd 23411_UnfoldingPreparation/ && make RunAll)

NominalUnfold:
	(cd 23412_ActualUnfold && make Prepare RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunDataUnfold)

MCIterationScan:
	(cd 23412_PerfectRecoGeneration/ && make Prepare TestRun)
	(cd 23412_FakeData/ && make Prepare TestRun)
	(cd 23412_ActualUnfold && make RunIterationStudies)
	(cd 23412_UnfoldIteration/ && make Prepare TestRun)
	(cd 23415_SVDRegularization/ && make Prepare TestRun)
	echo
	echo "=============================================================="
	echo "Please change the iteration count in data iteration scan input"
	echo "=============================================================="
	echo

DataIterationScan:
	(cd 23412_PerfectRecoGeneration/ && make TestRunData)
	(cd 23412_FakeData/ && make TestRunData)
	(cd 23412_ActualUnfold && make RunDataIterationStudies)
	(cd 23412_UnfoldIteration/ && make TestRunData)
	(cd 23415_SVDRegularization/ && make TestRunData)
	#
	# "=============================================================="
	# "Please change the iteration count in systematics"
	# "Please change the SVD regularization in systematics"
	# "Please change the iteration count in final output code"
	# "=============================================================="
	#

Systematics:
	(cd 23412_Systematics && make Prepare RunData RunDataPlot)

FinalPlot:
	(cd 23417_UnfoldedPaperPlot && make Prepare RunTest)
	(cd 23416_SystematicsPaperPlot && make Prepare RunTest)
	(cd 23416_SmearingMatrixPaperPlot && make Prepare RunTest)


