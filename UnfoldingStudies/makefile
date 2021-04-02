

JetClustering:
	(cd 23411_JetResponseClustering/ && make TestRun TestRunCut TestRunNoResidual TestRunNoJEC)

UnfoldPreparation:
	(cd 23411_UnfoldingPreparation/ && make RunAll)

NominalUnfold:
	(cd 23412_ActualUnfold && make Prepare RunDataUnfoldNominal RunDataUnfold RunMCUnfold)

MCIterationScan:
	(cd 23412_PerfectRecoGeneration/ && make Prepare TestRun)
	(cd 23412_FakeData/ && make Prepare TestRun)
	(cd 23412_ActualUnfold && make RunIterationStudies)
	(cd 23412_UnfoldIteration/ && make Prepare TestRun)
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
	#
	# "=============================================================="
	# "Please change the iteration count in systematics"
	# "Please change the iteration count in final output code"
	# "=============================================================="
	#

Systematics:
	(cd 23412_Systematics && make Prepare RunData RunDataPlot)

FinalPlot:
	(cd 23412_UnfoldedPaperPlot && make Prepare RunTest)

