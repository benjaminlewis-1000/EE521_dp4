#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream> // Read in files 
#include <string.h> // String manipulation
#include <vector> 
#include <algorithm>
#include <bitset>

#define DEBUG 1
#define READIN 1

#ifndef CONTAINER_LENGTH
#define CONTAINER_LENGTH (sizeof(unsigned long long) * 8)
#endif

#include "dataStructs.h"
#include "greedy.h"
#include "backtrack.h"

// TODO : Our numUncovered is initialize wrong.

using namespace std;

void printSubset(subsetContainer *subset){
    for(int i = 0; i < subset->arraySize; i++){
        cout << i << ": " << bitset<CONTAINER_LENGTH >(subset->elements[i]) << " " << endl;
    }
}

bool isSubsetRedundant(subsetContainer a, vector<subsetContainer> b){
	for (int i = 0; i < b.size(); i++){
		if (a.subsetNumber == b[i].subsetNumber){
			continue;
		}
		
		bool redundant = true;
		for (int j = 0; j < b[0].elements.size(); j++){
			redundant = redundant &&  ( ( b[i].elements[j] | a.elements[j] ) == b[i].elements[j] );
		}
		if (redundant){
			return true;
		}
	}
	return false;
}

/**
 * linCombos returns the indexes unique subsets in *subsets*
 * that are not linear combinations of the other subsets and
 * the given *solution*
 **/
/*vector<int> linCombos(std::vector<subsetContainer> &subsets, 
        std::vector<uint64_t> solution){
    vector<int> uniqueSubsets;
    for (int i = 0; i < subsets.size(), i++){
        std::vector<uint64_t> tmp;
        for (int j = 0; j < subsets[0].arraySize; j++){
            tmp.push_back(solution[j]);
        }
        for (int k = 0; k < subsets.size(); k++){
            for (int j = 0; j < subsets.arraySize; j++){
                if (i != j){
                    tmp[j] = tmp[j] & substeps[k].elements[j];
                }
            }
        }
        bool unique = 1;
        for (int j = 0; j < subsets.arraySize; j++){
            unique = unique && (tmp[j]^subsets[i].elements[j])
        } 
        if(unique){
            uniqueSubsets.push_back(i);
        }
    }
	return uniqueSubsets;
}*/

vector<subsetContainer> deleteRedundantSubsets(vector<subsetContainer> subsets){
	// sort by size
	
	sort(subsets.begin(), subsets.end(), sortSubsetMinSize);
	
	vector<subsetContainer> pruned;
	int subsetNum = 0; 
	for(int i = 0; i < subsets.size(); i++){
		if( ! (isSubsetRedundant(subsets[i], subsets) ) ){
			subsets[i].subsetNumber = subsetNum++;
			pruned.push_back(subsets[i]);
		}
	}
	return pruned;
}

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Usage: ./main sets.txt" << endl;
        return -1;
    }
    
    ifstream readFile;
    readFile.open(argv[1]);
    string line;
    // Size of universal set
    getline(readFile, line);
    int universeSize = atoi(line.c_str());
    // Number of subsets
    getline(readFile, line);
    int num_subsets = atoi(line.c_str());
    
    vector<subsetContainer> subsets;
    vector<vector<int> > subsets_decimal;
 //   subsetContainer subsets[num_subsets];
    for(int i = 0; i < num_subsets; i++){
    	subsetContainer temp;
        initSubset(&temp, universeSize); // FDM
    	subsets.push_back(temp);
        subsets[i].oldSubsetNumber = i;
        subsets[i].subsetNumber = i;
    }
    char* line2;
    char* sptr;
    for(int i = 0; i < num_subsets; i++){
        vector<int> decimal_names;
        getline(readFile, line);
        line2 = strdup(line.c_str());
        sptr = strtok(line2, " ");
       	int j = 0;
        while (sptr != NULL) {
        	int val = atoi(sptr);
            addElement(&subsets[i], val - 1); // FDM
            decimal_names.push_back(val);
            sptr = strtok(NULL," ");
        }
     //   printSubset(&temp);
        subsets[i].numUncoveredElements = popcount_3(subsets[i].elements, universeSize, subsets[0].arraySize) - ( CONTAINER_LENGTH - universeSize );
       // cout << "Pop count is " <<  popcount_3(subsets[i].elements, universeSize, subsets[0].arraySize) << endl;
#if(0)
       printSubset(&subsets[i]);
       cout << "Uncovered = " <<  subsets[i].numUncoveredElements  << endl;
#endif
       subsets_decimal.push_back(decimal_names);
    }
    
    std::sort (subsets.begin(), subsets.end(), sortSubsetListGreatest );
   
    // FDM - I commented out the rest of the program 
    vector<int> base_solution;
    
    greedy(subsets, base_solution, universeSize);
    
    
    int base_size = base_solution.size();
    cout << "Base solution size is of size " <<  base_solution.size() << endl;
    
/*    bool solved = checkSolution(subsets, base_solution, universeSize);
//    cout << (solved? "Solved" : "Not solved") << endl;*/
    process_solution(subsets_decimal, base_solution);
    
    /* Backtracking solution*/
    vector<subsetContainer> pruned = deleteRedundantSubsets(subsets);
    for (int i = 0; i < pruned.size(); i++){
    	cout << "Subset " << pruned[i].subsetNumber << endl;
    }

    vector<int> currentSolution;
    vector<int> bestSolution = base_solution;
    int bestSize = base_size;
    vector<uint64_t> solutionProgress;
    for(int i = 0; i < pruned[0].elements.size(); i++)
        solutionProgress.push_back(0);

  //  vector<int> uniqueSubsets = linCombos(pruned, solution);
   // vector<int> uniqueSubsetNames;
 /*   for(int i = 0; i < uniqueSubsets.size(); i++){ 
        // Save name
        
        // Add to solutionProgress
        for(int j = 0; j < subsets[0].arraySize; j++){

        }

        // Remove them from subsets
        pruned.erase(uniqueSubsets[i]);

        // Reduce minSize
        baseSize--;
    }*/

    /*
    cout << "Pruned size is " << pruned.size() << endl;
    for(int i = 0; i < pruned.size(); i++){
    	int index = pruned[i].oldSubsetNumber;
    	cout << "(" << index << ") ";
    	for(int k = 0; k < subsets_decimal[index].size(); k++)
    		cout << subsets_decimal[index][k] << " ";
    	cout << endl;
    }
    cout << "finish" << endl;*/
 /*   int** orderEnforcingArray = new int*[universeSize];
    for (int i = 0; i < universeSize; i++){
    	orderEnforcingArray[i] = new int[universeSize];
    	for (int j = 0; j < universeSize; j++){
    		orderEnforcingArray[i][j] = 0;
    	}
    }*/
    // Sort before calling backtrack
/*	sort(pruned.begin(), pruned.end(), sortSubsetListGreatest);

	cout << "pruned start at " << pruned[0].subsetNumber << endl;
	cout << "Uncovered is " << pruned[0].numUncoveredElements << endl;*/

    backtrack(pruned, pruned, subsets_decimal, currentSolution, 
            solutionProgress, universeSize, base_size, bestSolution);

    // Add unique sets to backtrack solution
/*    for(int i = 0; i < uniqueSets.size(); i++){

    }*/

    cout << "Best solution size is " << bestSolution.size() << endl;
    process_solution(subsets_decimal, bestSolution);
    
    return 0;

}
