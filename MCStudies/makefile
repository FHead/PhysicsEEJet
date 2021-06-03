

PrepareJEC:
	(cd 23474_JetResponseEnergy && make Prepare FullRun)

RunMCJEC:
	(cd 23474_JetResponseEnergy && make Prepare FullRun RunJEC)
	(cd 23474_JetResponseEnergy && make FullRun RunJECClosure)
	(cd 23474_JetResponseEnergy && make Deploy)

RunMCJER:
	(cd 23515_JetResolution/ && make Prepare TestRun Deploy)
