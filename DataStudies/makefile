
NominalJEC: RunDijetSideResidual RunMultiJetZUniformResidual

ExtraJECPlots: RunDijetResidualExploration RunMultiJetResidualExploration


RunDijetSideResidual:
	(cd 23475_DataMCComparisonEnergy && make Prepare FullRun)
	(cd 23475_DataRelativeResidualEnergy && make Prepare TestRun TestRunSummary TestRunExport Deploy)

RunMultiJetZUniformResidual:
	(cd 23475_DataMCComparisonEnergy && make Prepare FullRun)
	(cd 23475_DataZPeakUniformityEnergy && make Prepare ProductionRun RunExport Deploy)

RunDijetResidualExploration:
	(cd 23475_DataMCComparisonEnergy && make Prepare FullRun)
	(cd 23475_DataDijetResidualEnergy && make Prepare TestRun)

RunMultiJetResidualExploration:
	(cd 23475_DataMCComparisonEnergy && make Prepare FullRun)
	(cd 23475_DataZPeakResidualEnergy && make Prepare TestRun RunNScan RunXScan RunXScanV2 RunNScanV2 RunXScanV3 RunHarvest)

RunDijetResolution:
	(cd 23515_DataDijetResolution && make Prepare TestRun RunSummary)
