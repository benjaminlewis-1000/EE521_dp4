// greedy.h

#ifndef GREEDY_H
#define GREEDY_H

#define UPDATE_DEBUG 0
#if(UPDATE_DEBUG)
	using namespace std;
#endif

///checkSolution(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize)

#include "dataStructs.h"

int update_subsets(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize);

void greedy(std::vector<subsetContainer> &subsets, std::vector<int> &selections, int universeSize){
#if (DEBUG && UPDATE_DEBUG)
	sleep(1);
#endif

	std::sort(subsets.begin(), subsets.end(), sortSubsetListGreatest);
	
	if (subsets[0].numUncoveredElements == 0 ){
		// Base case, nothing left
		return;
	}
	
	int selection = subsets[0].subsetNumber; // Get subset with greatest # of uncovered elements
	selections.push_back(selection);
	
	std::vector<subsetContainer> updatedSubsets = subsets;
	
	update_subsets(updatedSubsets, selections, universeSize);

#if (DEBUG && UPDATE_DEBUG)
	cout << subsets[0].numUncoveredElements << "   " ;
	cout << updatedSubsets[0].numUncoveredElements << endl;
#endif
	
	greedy(updatedSubsets, selections, universeSize);
	
	// Add to selections
	// Update subsets by number of unused elements left
}

int update_subsets(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){
	// Initialize a vector of elements that have been hit.
	char hitElements[universeSize];
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	for (int i = 0; i < universeSize; i++){
		// Initialize every element to 0 (uncovered)
		hitElements[i] = 0;
	}
	
	for (int i = 0; i < selections.size(); i++){
		int subsetIndex = selections[i];
		for (int j = 0; j < subsets[subsetIndex].elements.size(); j++){
			int element = subsets[subsetIndex].elements[j];
			hitElements[element - 1 ] = 1; // Subtract 1 for [1..n] elements
		}
	}
	
	// Update the numUncoveredElements for each subset.
	for (int i = 0; i < subsets.size(); i++){
		int uncovered = 0; 
		for (int j = 0; j < subsets[i].elements.size(); j++){
			int element = subsets[i].elements[j];
			if (hitElements[element - 1] == 0){
				uncovered++;
			}
		}
		subsets[i].numUncoveredElements = uncovered;
		#if (DEBUG && UPDATE_DEBUG)
			cout << uncovered << " elements uncovered\n";
		#endif
	} 
	
	int uncoveredRemaining = 0; 
	for (int i = 0; i < universeSize; i++){
		if (hitElements[i] == 0){
			uncoveredRemaining++;
		}
	}
	
	return uncoveredRemaining;
}


#endif
