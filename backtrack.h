// backtrack.h

#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "dataStructs.h"
#include <math.h>

using namespace std;

void backtrack(std::vector<subsetContainer> subsetFull, std::vector<subsetContainer> subsets, std::vector<int> currentSolution, int universeSize, int &minSize, std::vector<int> &bestSolution){

	//if (currentSolution.size() > 0 && currentSolution[0] == 3)
	//	sleep(1);
	for (int i = 0; i < currentSolution.size(); i++){
		 cout << currentSolution[i] << " ";
	}
	cout << std::endl;

	if (checkSolution(subsetFull, currentSolution, universeSize) ){
		// Is a solution
		// Update minimum size
		// Save off current best solution
		if (currentSolution.size() < minSize){
			bestSolution = currentSolution;
			minSize = currentSolution.size();
			cout << "New solution is ";
			for (int i = 0; i < currentSolution.size(); i++){
				 cout << currentSolution[i] << " ";
			}
			cout << endl;
		}
	} else if (currentSolution.size() + 1 >= minSize) { 
		// Prune backtracking tree
		return;
	} else {
		for (int i = 0; i < subsets.size(); i++){
		
			std::vector<int> solutionCopy = currentSolution;
			// Add elements from subsetsCopy.begin() + i to solutionCopy
			//cout << "Erasing element " << i << " from a subset of size " << subsets.size() << endl;
			
			solutionCopy.push_back(subsets[i].subsetNumber);
			
			std::vector<subsetContainer> subsetsCopy = subsetFull;
			int uncoveredRemaining = update_subsets(subsetsCopy, solutionCopy, universeSize);
			std::sort(subsetsCopy.begin(), subsetsCopy.end(), sortSubsetListGreatest);
			while(subsetsCopy.size() > 0 && subsetsCopy[subsetsCopy.size() - 1 ].numUncoveredElements == 0 ){
				subsetsCopy.erase(subsetsCopy.end() );
			}
			
			int iterationsRemaining = minSize - solutionCopy.size() ;
			int bestCase = 0;
			for (int k = 0; k < iterationsRemaining; k++){
				bestCase += subsetsCopy[k].numUncoveredElements;
			}
			
		//	cout << "  (" << iterationsRemaining << ") " << bestCase << " - " << uncoveredRemaining << endl; 
			//double scaleFactor = 1.0;
			/*if (iterationsRemaining < 2)
			 	scaleFactor = 1;*/
			if (bestCase < uncoveredRemaining){
				continue;
			}else{
				backtrack(subsetFull, subsetsCopy, solutionCopy, universeSize, minSize, bestSolution);
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
