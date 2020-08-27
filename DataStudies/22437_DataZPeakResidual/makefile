
default: RunResidual


TestRun: Execute
	./Execute --Input DataAll.root --Output DataSkimmed.root
	./Execute --Input MCAll.root --Output MCSkimmed.root

Execute: Skim.cpp
	CompileRootMacro Skim.cpp Execute

ExecuteResidual: Residual.cpp
	CompileRootMacro Residual.cpp ExecuteResidual

RunResidual: ExecuteResidual
	./ExecuteResidual --Data DataSkimmed.root --MC MCSkimmed.root --Output ZResidual.pdf
	cp ZResidual.pdf ~/WindowsHome/Downloads/
	cat JECRelativeResidual.txt | sed "s/1 0 0 0$$/`cat Snippet.txt`/" > JECResidual.txt

ExecuteThetaResidual: ThetaResidual.cpp
	CompileRootMacro ThetaResidual.cpp ExecuteThetaResidual

RunThetaResidual: ExecuteThetaResidual
	./ExecuteThetaResidual --Data DataSkimmed.root --MC MCSkimmed.root --Output ZResidualTheta.pdf
	cp ZResidualTheta.pdf ~/WindowsHome/Downloads/
