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

void backtrack(std::vector<subsetContainer> subsetFull, 
        std::vector<subsetContainer> subsets, std::vector<vector<int> > subsets_decimal, 
        std::vector<int> currentSolution, std::vector<uint64_t> solutionProgress,  
        int universeSize, int &minSize, std::vector<int> &bestSolution, int** orderEnforced){
        
       //cout << "Called " << endl;
    
    /*if (currentSolution.size() == 1){
    	cout << "Starting with "<<  currentSolution[0] << endl;
    }*/
	for (int i = 0; i < currentSolution.size(); i++){
		 cout << currentSolution[i] << " ";
	}
	//cout << bitset<CONTAINER_LENGTH >(solutionProgress[0]);
	cout << std::endl;

	if ( checkBacktrackSolution(solutionProgress) ){
		// Is a solution
		// Update minimum size
		// Save off current best solution
		if (currentSolution.size() < minSize){
			bestSolution = currentSolution;
			minSize = currentSolution.size();
			cout << "New solution is of size " << minSize << endl;
            process_solution(subsets_decimal, currentSolution);
			/*for (int i = 0; i < currentSolution.size(); i++){
				 cout << currentSolution[i] << " ";
			}
			cout << endl;*/
		}
	} else if (currentSolution.size() + 1 >= minSize) { 
		// Prune backtracking tree
		return;
	} else {
		for (int i = 0; i < subsets.size(); i++){
		
			std::vector<int> solutionCopy = currentSolution;
			int preceeding;
			if (currentSolution.size() > 0){
				preceeding = currentSolution[currentSolution.size() - 1] - 1; // 1 indexed to 0 indexed
			}else{
				preceeding = -1; // This is the first item in this branch.
			}
			// Add elements from subsetsCopy.begin() + i to solutionCopy
			//cout << "Erasing element " << i << " from a subset of size " << subsets.size() << endl;
			
			solutionCopy.push_back(subsets[i].subsetNumber);
            vector<uint64_t> solProgC = addSetToSolution(solutionProgress, subsets[i]);
			
			std::vector<subsetContainer> subsetsCopy = subsetFull;
			// update_subsets returns the number of elements already in joined subsets,
			// but we need universeSize - that number for uncoveredRemaining.
			int uncoveredRemaining =  universeSize - update_subsets(subsetsCopy, solutionCopy, universeSize) ;
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
			
		  //  cout << "  (" << iterationsRemaining << ") " << bestCase << " - " << uncoveredRemaining << endl; 
		/*	double scaleFactor = 1.0;
			if (iterationsRemaining > 10)
			 	scaleFactor = 0.6;
			else if (iterationsRemaining < 2)
				scaleFactor = 1;
			else{
				scaleFactor = (30.0 - (double) iterationsRemaining)/30.0*0.8;
				//cout<< "(" << iterationsRemaining << ") - " << scaleFactor << endl;
			}*/
			if (bestCase < uncoveredRemaining){
				continue;
			}else{
				// Solution is .... s_{n-1}, s_{n}. Preceeding is the set number of s_{n-1}, 
				// thisRound is the set number of s_{n}. Both are shifted to 0 indexing to work
				// with the 2D array, which is 0 indexed.
				int thisRound = solutionCopy[solutionCopy.size() - 1] - 1; // 1 indexed to 0 indexed
				bool preceeding_not_valid = (preceeding == -1); // I.e. this is the start of a major branch of size 1.
				std::cout << "thisRound " << thisRound << " Preceeding: " << preceeding << std::endl;
				std::cout << "Solution size is " << solutionCopy.size() << std::endl;
				for (int z = 0; z < solutionCopy.size(); z++){
					std::cout << solutionCopy[z] << " ";
				}
				std::cout << "\n";
				bool combination_not_covered;
				if (preceeding_not_valid || thisRound < 0){
					combination_not_covered = true;
				}else{
					combination_not_covered = (orderEnforced[thisRound][preceeding] == 0);
				}
				if ( preceeding_not_valid || combination_not_covered ){
					backtrack(subsetFull, subsetsCopy, subsets_decimal, solutionCopy, solProgC, universeSize, minSize, bestSolution, orderEnforced);
				}
				if (preceeding != -1){
					orderEnforced[thisRound][preceeding] = 1;
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
	//		update_subsets(subsetFull, solutionCopy, universeSize);
			
			// Pick the element
			// Copy the subsets and remove the elements
			// Recursive backtrack
		}
	}

}



#endif
