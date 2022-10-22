run:
	g++ src/*.cpp -o mrst
	./mrst < input.txt
test:
	g++ src/.cpp test/*.cpp -o
	