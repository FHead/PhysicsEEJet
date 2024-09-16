
default: all

all: library/BasicUtilities.o library/CATree.o library/Dictionary.o library/TauHelperFunctions3.o library/DrawRandom.o library/DrawRandom2.o

library/BasicUtilities.o: source/BasicUtilities.cpp include/BasicUtilities.h
	g++ source/BasicUtilities.cpp -Iinclude -c -o library/BasicUtilities.o -I${RootMacrosBase}/ -std=c++11

library/CATree.o: source/CATree.cpp include/CATree.h
	g++ source/CATree.cpp -Iinclude -c -o library/CATree.o -I${RootMacrosBase}/ -std=c++11

library/TauHelperFunctions3.o: source/TauHelperFunctions3.cpp include/TauHelperFunctions3.h
	g++ source/TauHelperFunctions3.cpp -Iinclude -c -o library/TauHelperFunctions3.o -I${RootMacrosBase}/ -std=c++11

library/DrawRandom.o: source/DrawRandom.cpp include/DrawRandom.h
	g++ source/DrawRandom.cpp -Iinclude -c -o library/DrawRandom.o -I${RootMacrosBase}/ -std=c++11

library/DrawRandom2.o: source/DrawRandom2.cpp include/DrawRandom2.h
	g++ source/DrawRandom2.cpp -Iinclude -c -o library/DrawRandom2.o -I${RootMacrosBase}/ -std=c++11

library/Dictionary.o: include/Dictionary.h include/DictionaryObject.h
	rootcint -f source/Dictionary.cxx -c include/DictionaryObject.h include/Dictionary.h
	g++ `root-config --cflags` source/Dictionary.cxx -o library/Dictionary.o -Iinclude -I. -c -fpic

