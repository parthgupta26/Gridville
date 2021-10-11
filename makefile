algorithmmake: algorithm.cpp
	g++ algorithm.cpp -o AlgoTowers -std=c++11

clean:
	@rm -f AlgoTowers
