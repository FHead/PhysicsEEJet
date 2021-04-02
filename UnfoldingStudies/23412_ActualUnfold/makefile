
default: RunThrustUnfold

UnfoldAll: RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunThrustUnfold UnfoldIterations

UnfoldIterations: RunIterationStudies RunDataIterationStudies

Prepare:
	ln -sf ../23411_UnfoldingPreparation/Output Input
	ln -sf ../23412_FakeData/Output InputToy
	mkdir -p Unfolded Plots

RunStatistics: Execute
	for i in `seq 1207 1250`; do \
		./Execute --Input InputToy/ToyDataJetEStatistics_$${i}.root --Output Unfolded/ToyDataJetEStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetZGStatistics_$${i}.root --Output Unfolded/ToyDataJetZGStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetRGStatistics_$${i}.root --Output Unfolded/ToyDataJetRGStatistics_$${i}.root; \
	done

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
	./Execute --Input InputToy/ToyJetENominal.root --Output Unfolded/ToyJetENominal.root
	./Execute --Input InputToy/ToyJetZGNominal.root --Output Unfolded/ToyJetZGNominal.root
	./Execute --Input InputToy/ToyJetRGNominal.root --Output Unfolded/ToyJetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyJetENominal.root --Original InputToy/ToyJetENominal.root \
		--Output Plots/ToyJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyJetZGNominal.root --Original InputToy/ToyJetZGNominal.root \
		--Output Plots/ToyJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyJetRGNominal.root --Original InputToy/ToyJetRGNominal.root \
		--Output Plots/ToyJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataIterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataJetENominal.root --Output Unfolded/ToyDataJetENominal.root
	./Execute --Input InputToy/ToyDataJetZGNominal.root --Output Unfolded/ToyDataJetZGNominal.root
	./Execute --Input InputToy/ToyDataJetRGNominal.root --Output Unfolded/ToyDataJetRGNominal.root
	./ExecutePlot --Input Unfolded/ToyDataJetENominal.root --Original InputToy/ToyDataJetENominal.root \
		--Output Plots/ToyDataJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataJetZGNominal.root --Original InputToy/ToyDataJetZGNominal.root \
		--Output Plots/ToyDataJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/ToyDataJetRGNominal.root --Original InputToy/ToyDataJetRGNominal.root \
		--Output Plots/ToyDataJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunDataUnfoldNominal: Execute ExecutePlot
	./Execute --Input Input/DataJetENominal.root --Output Unfolded/DataJetENominal.root
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGNominal.root
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGNominal.root
	./Execute --Input Input/DataJetZG2Nominal.root --Output Unfolded/DataJetZG2Nominal.root
	./Execute --Input Input/DataJetRG2Nominal.root --Output Unfolded/DataJetRG2Nominal.root
	./ExecutePlot --Input Unfolded/DataJetENominal.root --Original Input/DataJetENominal.root \
		--Output Plots/DataJetENominal.pdf --Iteration 14
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
	./Execute --Input Input/DataJetENominal.root --Output Unfolded/DataJetEMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetELargeThetaGap.root --Output Unfolded/DataJetELargeThetaGap.root
	./Execute --Input Input/DataJetZGLargeThetaGap.root --Output Unfolded/DataJetZGLargeThetaGap.root
	./Execute --Input Input/DataJetRGLargeThetaGap.root --Output Unfolded/DataJetRGLargeThetaGap.root
	./Execute --Input Input/DataJetENoResidual.root --Output Unfolded/DataJetENoResidual.root
	./Execute --Input Input/DataJetZGNoResidual.root --Output Unfolded/DataJetZGNoResidual.root
	./Execute --Input Input/DataJetRGNoResidual.root --Output Unfolded/DataJetRGNoResidual.root
	./Execute --Input Input/DataJetEJECUp.root --Output Unfolded/DataJetEJECUp.root
	./Execute --Input Input/DataJetZGJECUp.root --Output Unfolded/DataJetZGJECUp.root
	./Execute --Input Input/DataJetRGJECUp.root --Output Unfolded/DataJetRGJECUp.root
	./Execute --Input Input/DataJetEJECDown.root --Output Unfolded/DataJetEJECDown.root
	./Execute --Input Input/DataJetZGJECDown.root --Output Unfolded/DataJetZGJECDown.root
	./Execute --Input Input/DataJetRGJECDown.root --Output Unfolded/DataJetRGJECDown.root
	./Execute --Input Input/DataJetEJECHalfUp.root --Output Unfolded/DataJetEJECHalfUp.root
	./Execute --Input Input/DataJetZGJECHalfUp.root --Output Unfolded/DataJetZGJECHalfUp.root
	./Execute --Input Input/DataJetRGJECHalfUp.root --Output Unfolded/DataJetRGJECHalfUp.root
	./Execute --Input Input/DataJetEJECHalfDown.root --Output Unfolded/DataJetEJECHalfDown.root
	./Execute --Input Input/DataJetZGJECHalfDown.root --Output Unfolded/DataJetZGJECHalfDown.root
	./Execute --Input Input/DataJetRGJECHalfDown.root --Output Unfolded/DataJetRGJECHalfDown.root
	./Execute --Input Input/DataJetEJERUp.root --Output Unfolded/DataJetEJERUp.root
	./Execute --Input Input/DataJetZGJERUp.root --Output Unfolded/DataJetZGJERUp.root
	./Execute --Input Input/DataJetRGJERUp.root --Output Unfolded/DataJetRGJERUp.root
	./Execute --Input Input/DataJetEJERDown.root --Output Unfolded/DataJetEJERDown.root
	./Execute --Input Input/DataJetZGJERDown.root --Output Unfolded/DataJetZGJERDown.root
	./Execute --Input Input/DataJetRGJERDown.root --Output Unfolded/DataJetRGJERDown.root
	./ExecutePlot --Input Unfolded/DataJetEMCPrior.root --Original Input/DataJetENominal.root \
		--Output Plots/DataJetEMCPrior.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGMCPrior.root --Original Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGMCPrior.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 11
	./ExecutePlot --Input Unfolded/DataJetRGMCPrior.root --Original Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGMCPrior.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 7
	./ExecutePlot --Input Unfolded/DataJetENoResidual.root --Original Input/DataJetENoResidual.root \
		--Output Plots/DataJetENoResidual.pdf
	./ExecutePlot --Input Unfolded/DataJetZGNoResidual.root --Original Input/DataJetZGNoResidual.root \
		--Output Plots/DataJetZGNoResidual.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGNoResidual.root --Original Input/DataJetRGNoResidual.root \
		--Output Plots/DataJetRGNoResidual.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJECUp.root --Original Input/DataJetEJECUp.root \
		--Output Plots/DataJetEJECUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECUp.root --Original Input/DataJetZGJECUp.root \
		--Output Plots/DataJetZGJECUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECUp.root --Original Input/DataJetRGJECUp.root \
		--Output Plots/DataJetRGJECUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJECDown.root --Original Input/DataJetEJECDown.root \
		--Output Plots/DataJetEJECDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECDown.root --Original Input/DataJetZGJECDown.root \
		--Output Plots/DataJetZGJECDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECDown.root --Original Input/DataJetRGJECDown.root \
		--Output Plots/DataJetRGJECDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJECHalfUp.root --Original Input/DataJetEJECHalfUp.root \
		--Output Plots/DataJetEJECHalfUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfUp.root --Original Input/DataJetZGJECHalfUp.root \
		--Output Plots/DataJetZGJECHalfUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfUp.root --Original Input/DataJetRGJECHalfUp.root \
		--Output Plots/DataJetRGJECHalfUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJECHalfDown.root --Original Input/DataJetEJECHalfDown.root \
		--Output Plots/DataJetEJECHalfDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfDown.root --Original Input/DataJetZGJECHalfDown.root \
		--Output Plots/DataJetZGJECHalfDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfDown.root --Original Input/DataJetRGJECHalfDown.root \
		--Output Plots/DataJetRGJECHalfDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJERUp.root --Original Input/DataJetEJERUp.root \
		--Output Plots/DataJetEJERUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERUp.root --Original Input/DataJetZGJERUp.root \
		--Output Plots/DataJetZGJERUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJERUp.root --Original Input/DataJetRGJERUp.root \
		--Output Plots/DataJetRGJERUp.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75
	./ExecutePlot --Input Unfolded/DataJetEJERDown.root --Original Input/DataJetEJERDown.root \
		--Output Plots/DataJetEJERDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERDown.root --Original Input/DataJetZGJERDown.root \
		--Output Plots/DataJetZGJERDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5
	./ExecutePlot --Input Unfolded/DataJetRGJERDown.root --Original Input/DataJetRGJERDown.root \
		--Output Plots/DataJetRGJERDown.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75

RunMCUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetENominal.root --Output Unfolded/MCJetENominal.root
	# ./Execute --Input Input/MCLeadingJetENominal.root --Output Unfolded/MCLeadingJetENominal.root
	./Execute --Input Input/MCJetZGNominal.root --Output Unfolded/MCJetZGNominal.root
	./Execute --Input Input/MCJetRGNominal.root --Output Unfolded/MCJetRGNominal.root
	./ExecutePlot --Input Unfolded/MCJetENominal.root --Original Input/MCJetENominal.root \
		--Output Plots/MCJetENominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingJetENominal.root --Original Input/MCLeadingJetENominal.root \
		--Output Plots/MCLeadingJetENominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetZGNominal.root --Original Input/MCJetZGNominal.root \
		--Output Plots/MCJetZGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.5 --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetRGNominal.root --Original Input/MCJetRGNominal.root \
		--Output Plots/MCJetRGNominal.pdf --GenPrimaryMin 0 --GenPrimaryMax 0.75 \
		--RecoPrimaryMin 0 --RecoPrimaryMax 0.75 --Iteration 2

RunMCNoJECUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetENoJEC.root --Output Unfolded/MCJetENoJEC.root
	./ExecutePlot --Input Unfolded/MCJetENoJEC.root --Original Input/MCJetENoJEC.root \
		--Output Plots/MCJetENoJEC.pdf

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot
