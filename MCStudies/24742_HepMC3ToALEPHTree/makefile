
default: TestRun

TestRun: Execute
	./Execute --Input Meow.dat --Output Meow.root

TauHelperFunctions3.o: TauHelperFunctions3.cpp TauHelperFunctions3.h
	g++ TauHelperFunctions3.cpp -c -o TauHelperFunctions3.o

DrawRandom2.o: DrawRandom2.cpp DrawRandom2.h
	g++ DrawRandom2.cpp -c -o DrawRandom2.o

Execute: Convert.cpp TauHelperFunctions3.o DrawRandom2.o
	g++ Convert.cpp -o Execute `root-config --cflags --libs` TauHelperFunctions3.o DrawRandom2.o
