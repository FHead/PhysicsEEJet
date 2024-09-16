N = 100000

default: Execute
	echo Hello world

RunPythiaOnShell: Execute
	time ./Execute --Output PurePythia91.root --N $(N) --EPythia 91.2 --EBall 0 --Mean 0.2 --ExcludeE true

Execute: GeneratePythia.cpp
	g++ GeneratePythia.cpp -o Execute -std=c++17 \
		`fastjet-config --cxxflags --libs` \
		`root-config --cflags --libs` \
		$(ProjectBase)/CommonCode/library/Dictionary.o \
		-I$(ProjectBase)/CommonCode/include/
