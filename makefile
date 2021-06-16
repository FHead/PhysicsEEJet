

DeriveJetCorrection:
	(cd MCStudies/ && make PrepareJEC RunMCJEC RunMCJER)
	(cd DataStudies/ && make NominalJEC ExtraJECPlots)

Unfolding:
	(cd UnfoldingStudies/ && make RunAll)
