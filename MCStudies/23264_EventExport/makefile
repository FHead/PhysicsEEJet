

default: TestRun

TestRun: Execute
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall0_Mean020.root --n $$i > Pythia_Event$$i.txt; done
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall5_Mean020.root --n $$i > PythiaBall5_Event$$i.txt; done
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall10_Mean020.root --n $$i > PythiaBall10_Event$$i.txt; done
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall5_Mean060.root --n $$i > PythiaBall5_060_Event$$i.txt; done
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall10_Mean060.root --n $$i > PythiaBall10_060_Event$$i.txt; done
	# for i in `seq 1 1000`; do ./Execute --input Samples/PythiaBall20_Mean060.root --n $$i > PythiaBall20_060_Event$$i.txt; done
	for i in `seq 1 1000`; do ./Execute --input Samples/PurePythia89.root --n $$i > PurePythia89_Event$$i.txt; done
	for i in `seq 1 1000`; do ./Execute --input Samples/PurePythia91.root --n $$i > PurePythia91_Event$$i.txt; done
	for i in `seq 1 1000`; do ./Execute --input Samples/PurePythia93.root --n $$i > PurePythia93_Event$$i.txt; done
	mv *.txt txt/

Execute: ExportEvent.cpp
	CompileRootMacro ExportEvent.cpp Execute


