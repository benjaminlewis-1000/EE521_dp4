// greedy.h

#ifndef GREEDY_H
#define GREEDY_H

#define UPDATE_DEBUG 0
#if(UPDATE_DEBUG)
	using namespace std;
#endif

///checkSolution(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize)

#include "dataStructs.h"

int update_subsets_greedy(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize);

void greedy(std::vector<subsetContainer> &subsets, std::vector<int> &selections, int universeSize){
#if (DEBUG && UPDATE_DEBUG)
	sleep(1);
	for (int i = 0; i < selections.size(); i++){
		std::cout << selections[i] << " ";
	}
	std::cout << std::endl;
#endif

	std::sort(subsets.begin(), subsets.end(), sortSubsetListGreatest);
	
	if (subsets[0].numUncoveredElements == 0 ){
		// Base case, nothing left
		return;
	}
	
	int selection = subsets[0].subsetNumber; // Get subset with greatest # of uncovered elements
	selections.push_back(selection);
	
	std::vector<subsetContainer> updatedSubsets = subsets;
	
	update_subsets_greedy(updatedSubsets, selections, universeSize);

#if (DEBUG && UPDATE_DEBUG)
	std::sort(updatedSubsets.begin(), updatedSubsets.end(), sortSubsetListGreatest);
	cout << subsets[0].numUncoveredElements << "   " ;
	cout << updatedSubsets[0].numUncoveredElements << endl;
#endif
	
	greedy(updatedSubsets, selections, universeSize);
	
	// Add to selections
	// Update subsets by number of unused elements left
}

int update_subsets_greedy(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){

	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	std::vector<unsigned long long> currentSetBits;
    //	unsigned long long* currentSetBits = new unsigned long long [subsets[0].arraySize];
	for (int k = 0; k < subsets[0].arraySize; k++){
		currentSetBits.push_back(0);
	}
	for (int i = 0; i < selections.size(); i++){
		for (int j = 0; j < subsets[0].arraySize; j++){
			currentSetBits[j] |= subsets[ selections[i] ].elements[j];
		}
	}
	int uncoveredRemaining = popcount_3(currentSetBits, universeSize, subsets[0].arraySize) - ( CONTAINER_LENGTH - universeSize );
	
	// Now, tmp holds the set.
	for (int i = 0; i < subsets.size(); i++){
		std::vector<unsigned long long> tmp;
		for (int k = 0; k < subsets[0].arraySize; k++){
			tmp.push_back(0);
		}
		for (int j = 0; j < subsets[0].arraySize; j++){
			tmp[j] = (currentSetBits[j] | subsets[i].elements[j]) ^ currentSetBits[j];
		}
		subsets[i].numUncoveredElements = popcount_3(tmp, universeSize, subsets[0].arraySize);
	}
	
	return uncoveredRemaining;
	
}

#endif
