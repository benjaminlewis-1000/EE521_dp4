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
        
       //cout << "Called " << endl;
    
    /*if (currentSolution.size() == 1){
    	cout << "Starting with "<<  currentSolution[0] << endl;
    }*/
	/*for (int i = 0; i < currentSolution.size(); i++){
		 cout << currentSolution[i] << " ";
	}
	cout << std::endl;*/
    /*for(int j = 0; j < solutionProgress.size(); j++){
        cout << "  " << j << ": " << bitset<CONTAINER_LENGTH >(solutionProgress[j]) << " " << endl;
    }*/
  //  cout << "Best solution size is " << minSize << endl;
    //process_solution(subsets_decimal, bestSolution);

	if ( checkBacktrackSolution(solutionProgress) ){
		// Is a solution
		// Update minimum size
		// Save off current best solution
		if (currentSolution.size() < minSize){
			bestSolution = currentSolution;
			minSize = currentSolution.size();
		/*	cout << "New sub solution is of size " << minSize << ": " << endl;
			for (int i = 0; i < currentSolution.size(); i++){
				 cout << currentSolution[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < currentSolution.size(); i++){
				 cout << subsetFull[ currentSolution[i] ].oldSubsetNumber + 1 << " ";
			}
			cout << endl;
            process_solution(subsets_decimal, bestSolution);*/
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
			// Add elements from subsetsCopy.begin() + i to solutionCopy
			//cout << "Erasing element " << i << " from a subset of size " << subsets.size() << endl;
			
			solutionCopy.push_back(subsets[i].subsetNumber);
		//	std::cout << "Pushing back " << subsets[i].subsetNumber << std::endl;
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
			
		 //   cout << "  (" << iterationsRemaining << ") " << bestCase << " - " << uncoveredRemaining << endl; 
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
				// thisRound is the set number of s_{n}. 
				int thisRound = solutionCopy[solutionCopy.size() - 1] ; 
				bool preceeding_not_valid = (preceeding == -1); // I.e. this is the start of a major branch of size 1.
			//	std::cout << "thisRound " << thisRound << " Preceeding: " << preceeding << std::endl;
			//	std::cout << "Solution size is " << solutionCopy.size() << std::endl;
				/*for (int z = 0; z < solutionCopy.size(); z++){
					std::cout << solutionCopy[z] << " ";
				}
				std::cout << "\n";*/
				bool combination_not_covered;
				if (preceeding_not_valid){
					combination_not_covered = true;
				}else{
					combination_not_covered = (orderEnforced[thisRound][preceeding] == 0);
				}
				if ( preceeding_not_valid || combination_not_covered ){
					backtrack(subsetFull, subsetsCopy, subsets_decimal, solutionCopy, solProgC, universeSize, minSize, bestSolution, orderEnforced);
					if (preceeding != -1){
						orderEnforced[preceeding][thisRound] = 1;
					}
				}else{
				//	std::cout << "Pruned: " << preceeding << " has already been preceeded by " <<  thisRound << "(Already had a " << thisRound << ", " << preceeding << ")" << std::endl;
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
