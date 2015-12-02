// backtrack.h

#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "dataStructs.h"
#include <math.h>

using namespace std;

bool checkBacktrackSolution(std::vector<uint64_t> solutionProgress){ 
    bool test = 1;
    for(int i = 0; i < solutionProgress.size(); i++){
        test = test && ( ! (~solutionProgress[i] ) );
    }
    return test;
}

vector<uint64_t> addSetToSolution(std::vector<uint64_t> solutionProgress, 
        subsetContainer subset){
    for(int i = 0; i < subset.elements.size(); i++){
        solutionProgress[i] = solutionProgress[i] | subset.elements[i];
    }
    return solutionProgress;
}

int update_subsets_backtrack(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize, std::vector<uint64_t> solutionProgress){

	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
    //	unsigned long long* solutionProgress = new unsigned long long [subsets[0].arraySize];
	/*for (int i = 0; i < selections.size(); i++){
		for (int j = 0; j < subsets[0].arraySize; j++){
			solutionProgress[j] |= subsets[ selections[i] ].elements[j];
		}
	}*/
	int uncoveredRemaining = popcount_3(solutionProgress, universeSize, subsets[0].arraySize) - ( CONTAINER_LENGTH - universeSize );
	
	// Now, tmp holds the set.
	for (int i = 0; i < subsets.size(); i++){
		std::vector<unsigned long long> tmp;
		for (int k = 0; k < subsets[0].arraySize; k++){
			tmp.push_back(0);
		}
		for (int j = 0; j < subsets[0].arraySize; j++){
			tmp[j] = (solutionProgress[j] | subsets[i].elements[j]) ^ solutionProgress[j];
		}
		subsets[i].numUncoveredElements = popcount_3(tmp, universeSize, subsets[0].arraySize);
	}
	
	return uncoveredRemaining;
	
}


void backtrack(std::vector<subsetContainer> subsetFull, 
        std::vector<subsetContainer> subsets, std::vector<vector<int> > subsets_decimal, 
        std::vector<int> currentSolution, std::vector<uint64_t> solutionProgress,  
        int universeSize, int &minSize, std::vector<int> &bestSolution, int** orderEnforced,
        timeval tim, double startTime){

	if ( checkBacktrackSolution(solutionProgress) ){
		// Is a solution
		// Update minimum size
		// Save off current best solution
		if (currentSolution.size() < minSize){
			bestSolution = currentSolution;
			minSize = currentSolution.size();
		}
	} else if (currentSolution.size() + 1 >= minSize) { 
		// Prune backtracking tree
		return;
	} else {
		for (int i = 0; i < subsets.size(); i++){
		
			std::vector<int> solutionCopy = currentSolution;
			int preceeding;
			if (currentSolution.size() > 0){
				preceeding = currentSolution[currentSolution.size() - 1];
			}else{
				preceeding = -1; // This is the first item in this branch.
			}
			// Add elements from subsetsCopy.begin() + i to solutionCopy;
			
			solutionCopy.push_back(subsets[i].subsetNumber);
			
            vector<uint64_t> solProgC = addSetToSolution(solutionProgress, subsets[i]);
			
			std::vector<subsetContainer> subsetsCopy = subsetFull;
			// update_subsets_backtrack returns the number of elements already in joined subsets,
			// but we need universeSize - that number for uncoveredRemaining.
			int uncoveredRemaining =  universeSize - update_subsets_backtrack(subsetsCopy, solutionCopy, universeSize, solutionProgress) ;
			std::sort(subsetsCopy.begin(), subsetsCopy.end(), sortSubsetListGreatest);
			while(subsetsCopy.size() > 0 
                    &&  subsetsCopy[subsetsCopy.size() - 1 ].numUncoveredElements == 0 ){
				subsetsCopy.erase(subsetsCopy.end() );
			}
			
			int iterationsRemaining = minSize - solutionCopy.size() ;
			int bestCase = 0;
			
			//std::sort(subsetsCopy.begin(), subsetsCopy.end(), sortSubsetListGreatest);
			for (int k = 0; k < iterationsRemaining; k++){
				bestCase += subsetsCopy[k].numUncoveredElements;
			}
			
			if (bestCase < uncoveredRemaining){
				continue;
			}else{
				// Solution is .... s_{n-1}, s_{n}. Preceeding is the set number of s_{n-1}, 
				// thisRound is the set number of s_{n}. 
				int thisRound = solutionCopy[solutionCopy.size() - 1] ; 
				bool preceeding_not_valid = (preceeding == -1); // I.e. this is the start of a major branch of size 1.
				bool combination_not_covered;
				if (preceeding_not_valid){
					combination_not_covered = true;
				}else{
					combination_not_covered = (orderEnforced[thisRound][preceeding] == 0);
				}
				if ( preceeding_not_valid || combination_not_covered ){
					backtrack(subsetFull, subsetsCopy, subsets_decimal, solutionCopy, solProgC, universeSize, minSize, bestSolution, orderEnforced, tim, startTime);
					if (preceeding != -1){
						orderEnforced[preceeding][thisRound] = 1;
					}
				}
			}
			
			// Count how many are covered already
			
			// Copy over the subsetFull
			// Update subsetFull with currentSolution
			// Sort copy of ssF by index of input file
			// remove elements from copy of ssF based on currentSolution
			// End result: same vector as line 43, but with updated uncovered counts
			// Not even go down that line if uncovered == 0 
			
			// Sort them again? 
	//		update_subsets_backtrack(subsetFull, solutionCopy, universeSize);
			
			// Pick the element
			// Copy the subsets and remove the elements
			// Recursive backtrack
		}
	}

}



#endif
