
default: RunThrustUnfold

UnfoldIterations: RunIterationStudies RunDataIterationStudies RunDataRound2IterationStudies RunDataRound3IterationStudies

UnfoldAll: RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunThrustUnfold

RunThrustUnfold: Execute ExecutePlot
	./Execute --Input Input/MCThrustNominal.root --Output Unfolded/MCThrustNominal.root
	./Execute --Input Input/DataThrustNominal.root --Output Unfolded/DataThrustNominal.root
	./Execute --Input Input/MCThrustUniform.root --Output Unfolded/MCThrustUniform.root
	./Execute --Input Input/DataThrustUniform.root --Output Unfolded/DataThrustUniform.root
	./Execute --Input Input/MCNoCutThrustNominal.root --Output Unfolded/MCNoCutThrustNominal.root
	./Execute --Input Input/DataNoCutThrustNominal.root --Output Unfolded/DataNoCutThrustNominal.root
	./Execute --Input Input/MCNoCutThrustUniform.root --Output Unfolded/MCNoCutThrustUniform.root
	./Execute --Input Input/DataNoCutThrustUniform.root --Output Unfolded/DataNoCutThrustUniform.root
	./Execute --Input InputToy/ToyMCThrustNominal.root --Output Unfolded/ToyMCThrustNominal.root
	./ExecutePlot --Input Unfolded/MCThrustNominal.root --Original Input/MCThrustNominal.root \
		--Output Plots/MCThrustNominal.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/DataThrustNominal.root --Original Input/DataThrustNominal.root \
		--Output Plots/DataThrustNominal.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/MCThrustUniform.root --Original Input/MCThrustUniform.root \
		--Output Plots/MCThrustUniform.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/DataThrustUniform.root --Original Input/DataThrustUniform.root \
		--Output Plots/DataThrustUniform.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/MCNoCutThrustNominal.root --Original Input/MCNoCutThrustNominal.root \
		--Output Plots/MCNoCutThrustNominal.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/DataNoCutThrustNominal.root --Original Input/DataNoCutThrustNominal.root \
		--Output Plots/DataNoCutThrustNominal.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/MCNoCutThrustUniform.root --Original Input/MCNoCutThrustUniform.root \
		--Output Plots/MCNoCutThrustUniform.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/DataNoCutThrustUniform.root --Original Input/DataNoCutThrustUniform.root \
		--Output Plots/DataNoCutThrustUniform.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
	./ExecutePlot --Input Unfolded/ToyMCThrustNominal.root --Original InputToy/ToyMCThrustNominal.root \
		--Output Plots/ToyMCThrustNominal.pdf --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 \
		--RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0

RunIterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyJetPNominal.root --Output Unfolded/ToyJetPNominal.root
	./Execute --Input InputToy/ToyJetZGNominal.root --Output Unfolded/ToyJetZGNominal.root
	./Execute --Input InputToy/ToyJetRGNominal.root --Output Unfolded/ToyJetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyJetPNominal.root --Original InputToy/ToyJetPNominal.root \
		--Output Plots/ToyJetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyJetZGNominal.root --Original InputToy/ToyJetZGNominal.root \
		--Output Plots/ToyJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyJetRGNominal.root --Original InputToy/ToyJetRGNominal.root \
		--Output Plots/ToyJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataIterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataJetPNominal.root --Output Unfolded/ToyDataJetPNominal.root
	./Execute --Input InputToy/ToyDataJetZGNominal.root --Output Unfolded/ToyDataJetZGNominal.root
	./Execute --Input InputToy/ToyDataJetRGNominal.root --Output Unfolded/ToyDataJetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataJetPNominal.root --Original InputToy/ToyDataJetPNominal.root \
		--Output Plots/ToyDataJetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataJetZGNominal.root --Original InputToy/ToyDataJetZGNominal.root \
		--Output Plots/ToyDataJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataJetRGNominal.root --Original InputToy/ToyDataJetRGNominal.root \
		--Output Plots/ToyDataJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataRound2IterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataRound2JetPNominal.root --Output Unfolded/ToyDataRound2JetPNominal.root
	./Execute --Input InputToy/ToyDataRound2JetZGNominal.root --Output Unfolded/ToyDataRound2JetZGNominal.root
	./Execute --Input InputToy/ToyDataRound2JetRGNominal.root --Output Unfolded/ToyDataRound2JetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataRound2JetPNominal.root --Original InputToy/ToyDataRound2JetPNominal.root \
		--Output Plots/ToyDataRound2JetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataRound2JetZGNominal.root --Original InputToy/ToyDataRound2JetZGNominal.root \
		--Output Plots/ToyDataRound2JetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataRound2JetRGNominal.root --Original InputToy/ToyDataRound2JetRGNominal.root \
		--Output Plots/ToyDataRound2JetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataRound3IterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataRound3JetPNominal.root --Output Unfolded/ToyDataRound3JetPNominal.root
	./Execute --Input InputToy/ToyDataRound3JetZGNominal.root --Output Unfolded/ToyDataRound3JetZGNominal.root
	./Execute --Input InputToy/ToyDataRound3JetRGNominal.root --Output Unfolded/ToyDataRound3JetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataRound3JetPNominal.root --Original InputToy/ToyDataRound3JetPNominal.root \
		--Output Plots/ToyDataRound3JetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataRound3JetZGNominal.root --Original InputToy/ToyDataRound3JetZGNominal.root \
		--Output Plots/ToyDataRound3JetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataRound3JetRGNominal.root --Original InputToy/ToyDataRound3JetRGNominal.root \
		--Output Plots/ToyDataRound3JetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataRound4IterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataRound4JetPNominal.root --Output Unfolded/ToyDataRound4JetPNominal.root
	./Execute --Input InputToy/ToyDataRound4JetZGNominal.root --Output Unfolded/ToyDataRound4JetZGNominal.root
	./Execute --Input InputToy/ToyDataRound4JetRGNominal.root --Output Unfolded/ToyDataRound4JetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataRound4JetPNominal.root --Original InputToy/ToyDataRound4JetPNominal.root \
		--Output Plots/ToyDataRound4JetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataRound4JetZGNominal.root --Original InputToy/ToyDataRound4JetZGNominal.root \
		--Output Plots/ToyDataRound4JetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataRound4JetRGNominal.root --Original InputToy/ToyDataRound4JetRGNominal.root \
		--Output Plots/ToyDataRound4JetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataRound5IterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataRound5JetPNominal.root --Output Unfolded/ToyDataRound5JetPNominal.root
	./Execute --Input InputToy/ToyDataRound5JetZGNominal.root --Output Unfolded/ToyDataRound5JetZGNominal.root
	./Execute --Input InputToy/ToyDataRound5JetRGNominal.root --Output Unfolded/ToyDataRound5JetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataRound5JetPNominal.root --Original InputToy/ToyDataRound5JetPNominal.root \
		--Output Plots/ToyDataRound5JetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataRound5JetZGNominal.root --Original InputToy/ToyDataRound5JetZGNominal.root \
		--Output Plots/ToyDataRound5JetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataRound5JetRGNominal.root --Original InputToy/ToyDataRound5JetRGNominal.root \
		--Output Plots/ToyDataRound5JetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataRound6IterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataRound6JetPNominal.root --Output Unfolded/ToyDataRound6JetPNominal.root
	./Execute --Input InputToy/ToyDataRound6JetZGNominal.root --Output Unfolded/ToyDataRound6JetZGNominal.root
	./Execute --Input InputToy/ToyDataRound6JetRGNominal.root --Output Unfolded/ToyDataRound6JetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataRound6JetPNominal.root --Original InputToy/ToyDataRound6JetPNominal.root \
		--Output Plots/ToyDataRound6JetPNominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataRound6JetZGNominal.root --Original InputToy/ToyDataRound6JetZGNominal.root \
		--Output Plots/ToyDataRound6JetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataRound6JetRGNominal.root --Original InputToy/ToyDataRound6JetRGNominal.root \
		--Output Plots/ToyDataRound6JetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataUnfoldNominal: Execute ExecutePlot
	./Execute --Input Input/DataJetPNominal.root --Output Unfolded/DataJetPNominal.root
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGNominal.root
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGNominal.root
	./Execute --Input Input/DataJetZG2Nominal.root --Output Unfolded/DataJetZG2Nominal.root
	./Execute --Input Input/DataJetRG2Nominal.root --Output Unfolded/DataJetRG2Nominal.root
	./ExecutePlot --Input Unfolded/DataJetPNominal.root --Original Input/DataJetPNominal.root \
		--Output Plots/DataJetPNominal.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGNominal.root --Original Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 11
	./ExecutePlot --Input Unfolded/DataJetRGNominal.root --Original Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 7
	./ExecutePlot --Input Unfolded/DataJetZG2Nominal.root --Original Input/DataJetZG2Nominal.root \
		--Output Plots/DataJetZG2Nominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 11
	./ExecutePlot --Input Unfolded/DataJetRG2Nominal.root --Original Input/DataJetRG2Nominal.root \
		--Output Plots/DataJetRG2Nominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 7

RunDataUnfold: Execute ExecutePlot
	./Execute --Input Input/DataJetPNominal.root --Output Unfolded/DataJetPMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetPNoResidual.root --Output Unfolded/DataJetPNoResidual.root
	./Execute --Input Input/DataJetZGNoResidual.root --Output Unfolded/DataJetZGNoResidual.root
	./Execute --Input Input/DataJetRGNoResidual.root --Output Unfolded/DataJetRGNoResidual.root
	./Execute --Input Input/DataJetPJECUp.root --Output Unfolded/DataJetPJECUp.root
	./Execute --Input Input/DataJetZGJECUp.root --Output Unfolded/DataJetZGJECUp.root
	./Execute --Input Input/DataJetRGJECUp.root --Output Unfolded/DataJetRGJECUp.root
	./Execute --Input Input/DataJetPJECDown.root --Output Unfolded/DataJetPJECDown.root
	./Execute --Input Input/DataJetZGJECDown.root --Output Unfolded/DataJetZGJECDown.root
	./Execute --Input Input/DataJetRGJECDown.root --Output Unfolded/DataJetRGJECDown.root
	./Execute --Input Input/DataJetPJECHalfUp.root --Output Unfolded/DataJetPJECHalfUp.root
	./Execute --Input Input/DataJetZGJECHalfUp.root --Output Unfolded/DataJetZGJECHalfUp.root
	./Execute --Input Input/DataJetRGJECHalfUp.root --Output Unfolded/DataJetRGJECHalfUp.root
	./Execute --Input Input/DataJetPJECHalfDown.root --Output Unfolded/DataJetPJECHalfDown.root
	./Execute --Input Input/DataJetZGJECHalfDown.root --Output Unfolded/DataJetZGJECHalfDown.root
	./Execute --Input Input/DataJetRGJECHalfDown.root --Output Unfolded/DataJetRGJECHalfDown.root
	./Execute --Input Input/DataJetPJERUp.root --Output Unfolded/DataJetPJERUp.root
	./Execute --Input Input/DataJetZGJERUp.root --Output Unfolded/DataJetZGJERUp.root
	./Execute --Input Input/DataJetRGJERUp.root --Output Unfolded/DataJetRGJERUp.root
	./Execute --Input Input/DataJetPJERDown.root --Output Unfolded/DataJetPJERDown.root
	./Execute --Input Input/DataJetZGJERDown.root --Output Unfolded/DataJetZGJERDown.root
	./Execute --Input Input/DataJetRGJERDown.root --Output Unfolded/DataJetRGJERDown.root
	./ExecutePlot --Input Unfolded/DataJetPMCPrior.root --Original Input/DataJetPNominal.root \
		--Output Plots/DataJetPMCPrior.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGMCPrior.root --Original Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGMCPrior.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 11
	./ExecutePlot --Input Unfolded/DataJetRGMCPrior.root --Original Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGMCPrior.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 7
	./ExecutePlot --Input Unfolded/DataJetPNoResidual.root --Original Input/DataJetPNoResidual.root \
		--Output Plots/DataJetPNoResidual.pdf
	./ExecutePlot --Input Unfolded/DataJetZGNoResidual.root --Original Input/DataJetZGNoResidual.root \
		--Output Plots/DataJetZGNoResidual.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGNoResidual.root --Original Input/DataJetRGNoResidual.root \
		--Output Plots/DataJetRGNoResidual.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJECUp.root --Original Input/DataJetPJECUp.root \
		--Output Plots/DataJetPJECUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECUp.root --Original Input/DataJetZGJECUp.root \
		--Output Plots/DataJetZGJECUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECUp.root --Original Input/DataJetRGJECUp.root \
		--Output Plots/DataJetRGJECUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJECDown.root --Original Input/DataJetPJECDown.root \
		--Output Plots/DataJetPJECDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECDown.root --Original Input/DataJetZGJECDown.root \
		--Output Plots/DataJetZGJECDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECDown.root --Original Input/DataJetRGJECDown.root \
		--Output Plots/DataJetRGJECDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJECHalfUp.root --Original Input/DataJetPJECHalfUp.root \
		--Output Plots/DataJetPJECHalfUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfUp.root --Original Input/DataJetZGJECHalfUp.root \
		--Output Plots/DataJetZGJECHalfUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfUp.root --Original Input/DataJetRGJECHalfUp.root \
		--Output Plots/DataJetRGJECHalfUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJECHalfDown.root --Original Input/DataJetPJECHalfDown.root \
		--Output Plots/DataJetPJECHalfDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfDown.root --Original Input/DataJetZGJECHalfDown.root \
		--Output Plots/DataJetZGJECHalfDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfDown.root --Original Input/DataJetRGJECHalfDown.root \
		--Output Plots/DataJetRGJECHalfDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJERUp.root --Original Input/DataJetPJERUp.root \
		--Output Plots/DataJetPJERUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERUp.root --Original Input/DataJetZGJERUp.root \
		--Output Plots/DataJetZGJERUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJERUp.root --Original Input/DataJetRGJERUp.root \
		--Output Plots/DataJetRGJERUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetPJERDown.root --Original Input/DataJetPJERDown.root \
		--Output Plots/DataJetPJERDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERDown.root --Original Input/DataJetZGJERDown.root \
		--Output Plots/DataJetZGJERDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJERDown.root --Original Input/DataJetRGJERDown.root \
		--Output Plots/DataJetRGJERDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunMCUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetPNominal.root --Output Unfolded/MCJetPNominal.root
	./Execute --Input Input/MCJetZGNominal.root --Output Unfolded/MCJetZGNominal.root
	./Execute --Input Input/MCJetRGNominal.root --Output Unfolded/MCJetRGNominal.root
	./ExecutePlot --Input Unfolded/MCJetPNominal.root --Original Input/MCJetPNominal.root \
		--Output Plots/MCJetPNominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetZGNominal.root --Original Input/MCJetZGNominal.root \
		--Output Plots/MCJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetRGNominal.root --Original Input/MCJetRGNominal.root \
		--Output Plots/MCJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 2

RunMCNoJECUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetPNoJEC.root --Output Unfolded/MCJetPNoJEC.root
	./ExecutePlot --Input Unfolded/MCJetPNoJEC.root --Original Input/MCJetPNoJEC.root \
		--Output Plots/MCJetPNoJEC.pdf

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot
