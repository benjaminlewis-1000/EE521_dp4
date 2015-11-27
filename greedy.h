// greedy.h

#ifndef GREEDY_H
#define GREEDY_H

#include "dataStructs.h"

void greedy(vector<subsetContainer> subsets, vector<int> &selections){
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	
	// Add to selections
	// Update subsets by number of unused elements left
}



#endif
