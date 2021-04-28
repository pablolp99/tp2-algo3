#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include "algorithms.h"
#include "graphs.h"
#include "unionfind.h"


#define MEM_SIZE 300 // Variar +- 100
#define ASPIRATION_STALL 150 // Variar +- 50-100
#define MAX_ITERATIONS 3500 // No hace falta variar
#define MAX_VICINITY_SIZE 100
#define TERMINATION_CONDITION 300 // Variar +- 100

// 1 -> AGM
// 2 -> SE
// 3 -> NN
// 4 -> TSESM con 1
// 5 -> TSESM con 2
// 6 -> TSESM con 3
// 7 -> TSWSM con 1
// 8 -> TSWSM con 2
// 9 -> TSWSM con 3

int main() {
    srand(time(NULL));
    
    int testRepeats;
    string testCase;
    cin >> testRepeats >> testCase;

    ALGraph g = readALGraph();

    for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSESM_AGM " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();
		ALGraph cycle = tabuSearchWithExploredSolutionsMemory(g, heuristicAGM, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;
	}

	for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSESM_SE " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();	    	
    	ALGraph cycle = tabuSearchWithExploredSolutionsMemory(g, shortestEdge, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;
	}

	for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSESM_NN " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();	    	
    	ALGraph cycle = tabuSearchWithExploredSolutionsMemory(g, nearestNeighbour, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;	
	}

	for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSWSM_AGM " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();	    	
    	ALGraph cycle = tabuSearchWithStructureMemory(g, heuristicAGM, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;
	}

	for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSWSM_SE " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();	    	
    	ALGraph cycle = tabuSearchWithStructureMemory(g, shortestEdge, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;
	}

	for (int i = 0; i < testRepeats; ++i){
    	cout << testCase << " " << "TSWSM_NN " << i+1 << " ";
		auto t1 = chrono::high_resolution_clock::now();	    	
    	ALGraph cycle = tabuSearchWithStructureMemory(g, nearestNeighbour, getRandomSubVicinity, MEM_SIZE, MAX_VICINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		cout << cycle.getNodeCount() << " " << cycle.getTotalWeight() << " " << duration << " ";
		cout << MEM_SIZE << " " << ASPIRATION_STALL << " " << MAX_ITERATIONS << " " << MAX_VICINITY_SIZE << " " << TERMINATION_CONDITION << endl;
    }

    return 0;
}