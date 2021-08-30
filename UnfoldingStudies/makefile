

default: Systematics FinalPlot

RunAll: JetClustering UnfoldPreparation NominalUnfold MCIterationScan DataIterationScan LeadingJetCorrection Systematics FinalPlot

RunAllQuick: JetClustering UnfoldPreparation NominalUnfold MCIterationScan DataIterationScan Systematics FinalPlot

JetClustering:
	(cd 23514_JetResponseClustering/ && make Prepare RunGroup1 RunGroup2)

UnfoldPreparation:
	(cd 23411_UnfoldingPreparation/ && make Preparation23514 RunNominal)

NominalUnfold:
	(cd 23412_ActualUnfold && make Prepare RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunMCFakeUnfold)

MCIterationScan:
	(cd 23412_PerfectRecoGeneration/ && make Prepare TestRun)
	(cd 23412_FakeData/ && make Prepare TestRun)
	(cd 23412_ActualUnfold && make RunIterationStudies)
	(cd 23412_UnfoldIteration/ && make Prepare TestRun)
	(cd 23415_SVDRegularization/ && make Prepare TestRun)
	#
	# ==============================================================
	# Please change the iteration count in data iteration scan input
	# ==============================================================
	#

DataIterationScan:
	(cd 23412_PerfectRecoGeneration/ && make TestRunData)
	(cd 23412_FakeData/ && make TestRunData)
	(cd 23412_ActualUnfold && make RunDataIterationStudies)
	(cd 23412_UnfoldIteration/ && make TestRunData)
	(cd 23415_SVDRegularization/ && make TestRunData)
	#
	# ==============================================================
	# Please change the iteration count in systematics
	# Please change the SVD regularization in systematics
	# Please change the iteration count in final output code
	# ==============================================================
	#

LeadingJetCorrection:
	(cd 23472_LeadingDiJetStudies/ && make Prepare DebugRun RunCorrectionPlot)
	(cd 23545_LeadingDiJetUncertainty/ && make Prepare TestRun)
	(cd 23551_JetReweighting/ && make Prepare TestRun)
	(cd 23551_JetReweightingUncertainty && make Prepare TestRun)

Systematics:
	(cd 23412_Systematics && make Prepare RunData RunDataPlot)

FinalPlot:
	(cd 23715_UnfoldedPaperPlotWithMOD && make Prepare RunTest)
	(cd 23715_SystematicsPaperPlotWithMOD && make Prepare RunTest)
	(cd 23715_SmearingMatrixPaperPlotWithMOD && make Prepare RunTest)
	(cd 23721_SmearingMatrixPaperPlotSmallWithMOD && make Prepare RunTest)



