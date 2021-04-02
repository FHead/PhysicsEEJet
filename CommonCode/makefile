
default: all

all: library/BasicUtilities.o library/CATree.o library/Dictionary.o 

library/BasicUtilities.o: source/BasicUtilities.cpp include/BasicUtilities.h
	g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o -I$(HOME)/FHeadHelperCode/RootMacros/ -std=c++11

library/CATree.o: source/CATree.cpp include/CATree.h
	g++ source/CATree.cpp -I. -c -o library/CATree.o -I$(HOME)/FHeadHelperCode/RootMacros/ -std=c++11

library/Dictionary.o: include/Dictionary.h include/DictionaryObject.h
	rootcint -f source/Dictionary.cxx -c include/DictionaryObject.h include/Dictionary.h
	g++ `root-config --cflags` source/Dictionary.cxx -o library/Dictionary.o -I. -c -fpic

