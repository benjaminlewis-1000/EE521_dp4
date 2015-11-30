#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream> // Read in files 
#include <string.h> // String manipulation
#include <vector> 
#include <algorithm>

#define DEBUG 1
#define READIN 0

#include "dataStructs.h"
#include "greedy.h"
#include "backtrack.h"

using namespace std;

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
 //   subsetContainer subsets[num_subsets];
    
    for(int i = 0; i < num_subsets; i++){
    	subsetContainer temp;
    	subsets.push_back(temp);
   //     subsets[i] = new subsetContainer;
        subsets[i].subsetNumber = i;
      //  state[i] = UNDISCOVERED;
    }
    char* line2;
    char* sptr;
    #if(DEBUG && READIN)
    	cout << "Here with " << num_subsets << " subsets\n";
    #endif
    for(int i = 0; i < num_subsets; i++){
        getline(readFile, line);
        line2 = strdup(line.c_str());
        sptr = strtok(line2, " ");
    #if(DEBUG && READIN)
    	cout << line << endl;
        cout << "Hi .. " << sptr << endl;
    #endif
       	int j = 0;
        while (sptr != NULL) {
        #if(DEBUG && READIN)
        	cout << *sptr << ",\n";
        	if (sptr == NULL){
        		cout << " end\n";
        	}
        #endif
        	int val = atoi(sptr);
            subsets[i].elements.push_back(val);
            sptr = strtok(NULL," ");
        }
        subsets[i].numUncoveredElements = subsets[i].elements.size();
        #if(DEBUG && READIN)
        cout << endl << "fin " <<  endl;
        #endif
    }
    
    std::sort (subsets.begin(), subsets.end(), sortSubsetListGreatest );
    
    #if(DEBUG && READIN)
    	for (int i = 0; i < num_subsets; i++){
    		int j = 0;
    		for (int j = 0; j < subsets[i].elements.size(); j++){
    			cout << subsets[i].elements[j] << ", ";
    		}
    		cout << endl;
    	}
    #endif
    
    vector<int> base_solution;
    
    greedy(subsets, base_solution, universeSize);
    int base_size = base_solution.size();
    cout << "Base solution size is " <<  base_solution.size() << endl;
    
/*    bool solved = checkSolution(subsets, base_solution, universeSize);
//    cout << (solved? "Solved" : "Not solved") << endl;
    if (solved){
    	process_solution(subsets, base_solution);
    }*/
    
    vector<int> currentSolution;
    vector<int> bestSolution = base_solution;
	sort(subsets.begin(), subsets.end(), sortSubsetListGreatest);
    backtrack(subsets, subsets, currentSolution, universeSize, base_size, bestSolution);
  //  cout << bestSolution.size() << endl;
    
    process_solution(subsets, bestSolution);
    
  /*  solutions.push_back(4);
    solutions.push_back(3);
    solutions.push_back(2);
    bool solved = checkSolution(subsets, solutions, universeSize);
//    cout << (solved? "Solved" : "Not solved") << endl;
    if (solved){
    	process_solution(subsets, solutions);
    }*/
    
    return 0;

}
