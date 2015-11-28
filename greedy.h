// greedy.h

#ifndef GREEDY_H
#define GREEDY_H

#define UPDATE_DEBUG 0
#if(UPDATE_DEBUG)
	using namespace std;
#endif

#include "dataStructs.h"

void greedy(std::vector<subsetContainer> &subsets, std::vector<int> &selections, int universeSize){
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	
	int selection = subsets[0].subsetNumber;
	selections.push_back(selection);
	
	// Add to selections
	// Update subsets by number of unused elements left
}

void update_subsets(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){
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
}


#endif
