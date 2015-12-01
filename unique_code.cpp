/**
 * linCombos returns the indexes unique subsets in *subsets*
 * that are not linear combinations of the other subsets and
 * the given *solution*
 **/
vector<int> linCombos(std::vector<subsetContainer> &subsets, 
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
}
