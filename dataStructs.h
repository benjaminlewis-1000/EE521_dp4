// dataStructs.h - helper functions and data structures for the set coverage algorithm

#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define DATA_DEBUG 0
#if(DATA_DEBUG)
	using namespace std;
#endif

struct subsetContainer{
	int numUncoveredElements;
	int subsetNumber; // Order read in
	std::vector<int> elements;
};

bool sortSubsetList(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements < b.numUncoveredElements);
}

bool sortSubsetListGreatest(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements > b.numUncoveredElements);
}

bool sortSubsetListIndex(subsetContainer a, subsetContainer b){
	return (a.subsetNumber < b.subsetNumber);
}

bool checkSolution(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){
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
}

#endif
