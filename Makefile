run:
	g++ src/*.cpp -o mrst
	./mrst < input.txt > output
test:
	g++ src/tests/FindCFC.cpp src/GraphContainer.cpp src/utils.cpp -o test_cfc
	mv test_cfc src/bin/
	./src/bin/test_cfc