// dataStructs.h - helper functions and data structures for the set coverage algorithm

#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#ifndef CONTAINER_LENGTH
#define CONTAINER_LENGTH (sizeof(unsigned long long) * 8)
#endif

#define DATA_DEBUG 0
#if(DATA_DEBUG)
	using namespace std;
#endif

struct subsetContainer{
	int numUncoveredElements;
	int subsetNumber; // Order read in
    int arraySize;
    // unsigned long long int = 64 bits
	unsigned long long int* elements;
    int size;
};


/**
 * Initilizes subset
 *
 * Called on each subset before adding elements
 *
 * FDM
 * */
void initSubset(subsetContainer *subset, int universeSize){
    subset->arraySize = universeSize/CONTAINER_LENGTH;
    if (universeSize % CONTAINER_LENGTH != 0){
    	subset->arraySize += 1;
    }
    subset->elements = new unsigned long long [subset->arraySize];
    subset->size = 0;
    // Initialize elements to 0 for the universe
    for(int i = 0; i < subset->arraySize; i ++){
        subset->elements[i] = 0;
        // If it's the leftmost, init it to 1s.
        if ( i == subset->arraySize - 1 ){
	        subset->elements[i] = ~subset->elements[i];
	    }
    }
    
    // Rest of array are 1's (elements outside universe are 1)
    int shiftVal = universeSize % CONTAINER_LENGTH;
    subset->elements[subset->arraySize - 1] <<= shiftVal;
    
   /* for(int i = subset->arraySize * CONTAINER_LENGTH - universeSize; 
            i < subset->arraySize * CONTAINER_LENGTH; i++){
        std::cout << "It " << i << std::endl;
        subset->elements[subset->arraySize-1] = 
        	subset->elements[subset->arraySize-1] | (unsigned long long)(1 << i);
    }*/
}


/**
 * Adds an element *val* to *subset*
 *
 * FDM
 * */
void addElement(subsetContainer subset, int val){
    int index = (int) val / CONTAINER_LENGTH;
    int shift = val - index * CONTAINER_LENGTH; 
    subset.elements[index] = subset.elements[index] | (1 << shift);
    subset.size += 1;
}

/** 
 * Deconstructs subset after we are done with the program
 *
 * FDM
 */
void deleteSubset(subsetContainer subset){
    delete subset.elements;
}

// Sort by number of uncovered elements remaining, least to greatest.
bool sortSubsetList(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements < b.numUncoveredElements);
}

// Sort by number of uncovered elements remaining, greatest to least.
bool sortSubsetListGreatest(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements > b.numUncoveredElements);
}

// Sort in the order the subset was in the input file.
bool sortSubsetListIndex(subsetContainer a, subsetContainer b){
	return (a.subsetNumber < b.subsetNumber);
}

/**
 * checkSolution
 * 
 * Needs to be modified to be binary check solution - FDM
 * */
/*bool checkSolution(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){
	char hitElements[universeSize];
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	for (int i = 0; i < universeSize; i++){
		hitElements[i] = 0;
	}
	
	for (int i = 0; i < selections.size(); i++){
		int subsetIndex = selections[i];
		#if(DEBUG && DATA_DEBUG)
			cout << "Selection subset is " << subsetIndex << endl;
		#endif
		for (int j = 0; j < subsets[subsetIndex].elements.size(); j++){
			int element = subsets[subsetIndex].elements[j];
			#if(DEBUG && DATA_DEBUG)
				cout << "Element is " << element << endl;
			#endif
			hitElements[element - 1 ] = 1; // Subtract 1 for [1..n] elements
		}
	}
	
	bool solved = true;
	for (int i = 0; i < universeSize; i++){
		if (hitElements[i] == 0){
			solved = false;
			break;
		}
	}
	
	return solved;
}

void process_solution(std::vector <subsetContainer> subsets, std::vector<int> selections){
	std::sort(selections.begin(), selections.end());
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	std::cout << selections.size() << std::endl;
	for (int i = 0; i < selections.size(); i++){
		std::cout << "(" << selections[i] + 1 << ") ";
		for (int j = 0; j < subsets[ selections[i] ].elements.size(); j++){
			std::cout << subsets[ selections[i] ].elements[j] << " ";
		}
		std::cout << std::endl;
	}
}*/

#endif
