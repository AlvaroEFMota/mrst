run:
	g++ src/*.cpp -o mrst
	./mrst < input.txt
test:
	make test_heawood
	make test_four_sum
	make test_CFC
	make test_inadmissible_edges
	make test_pfaffian

output:
	g++ src/*.cpp -o mrst
	./mrst < input.txt > output.txt

test_heawood:
	g++ src/tests/test_heawood_verification.cpp src/GraphContainer.cpp src/PfaffianVerification.cpp -o test_heawood_verification
	mv test_heawood_verification src/bin/
	./src/bin/test_heawood_verification
test_four_sum:
	g++ src/tests/test_four_sum_decomposition.cpp src/GraphContainer.cpp src/FourSumDecomposition.cpp src/utils.cpp -o test_four_sum_decomposition
	mv test_four_sum_decomposition src/bin/
	./src/bin/test_four_sum_decomposition
test_CFC:
	g++ src/tests/FindCFC.cpp src/GraphContainer.cpp src/utils.cpp -o test_cfc
	mv test_cfc src/bin/
	./src/bin/test_cfc
test_inadmissible_edges:
	g++ src/tests/test_inadmissible_edges.cpp src/GraphContainer.cpp src/InadmissibleEdges.cpp -o test_inadmissble_edges
	mv test_inadmissble_edges src/bin/
	./src/bin/test_inadmissble_edges
test_pfaffian:
	g++ src/tests/test_pfaffian.cpp src/FourSumDecomposition.cpp src/GraphContainer.cpp src/InadmissibleEdges.cpp src/pfaffian.cpp src/PfaffianVerification.cpp src/TightCutDecomposition.cpp src/utils.cpp -o test_pfaffian
	mv test_pfaffian src/bin/
	./src/bin/test_pfaffian